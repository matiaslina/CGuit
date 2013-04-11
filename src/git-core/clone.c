#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "clone.h"
#include "common.h"

#define     FETCH_FORMAT     "net %3d%% (%4d kb, %5d/%5d) / idx %3d%% (%5d/%5d)\n"
#define     CHECKOUT_FORMAT  "chk %3d%% %u %u , File -> %s\n"

/* This function will not remain here.. it's just for debug */
static void print_progress (const progress_data *pd)
{
    gchar str_formatted[128]; // should be enought
    str_formatted[127] = '\0';

    if (!pd->path)
    {
        gint network_percent = ( 100 * pd->fetch_progress.received_objects) / pd->fetch_progress.total_objects;
        gint index_percent = (100 * pd->fetch_progress.indexed_objects) / pd->fetch_progress.total_objects;
        gint kbytes = pd->fetch_progress.received_bytes / 1024;

        sprintf (str_formatted,
                 FETCH_FORMAT, 
                 network_percent,
                 kbytes,
                 pd->fetch_progress.received_objects,
                 pd->fetch_progress.total_objects,
                 index_percent,
                 pd->fetch_progress.indexed_objects,
                 pd->fetch_progress.total_objects);

    }
    else
    {
        gint checkout_percent = pd->total_steps > 0
                            ? (100 * pd->completed_steps) / pd->total_steps
                            : 0.f;
        sprintf (str_formatted,
                 CHECKOUT_FORMAT,
                 checkout_percent,
                 pd->completed_steps,
                 pd->total_steps,
                 pd->path);

    }
}

static gint fetch_progress (const git_transfer_progress *stats, void *payload)
{
    progress_data *pd = (progress_data *) payload;
    pd->fetch_progress = *stats;
    print_progress (pd);
    return 0;
}

static void checkout_progress (const gchar  *path, 
                               size_t       current,
                               size_t       total,
                               void         *payload)
{
    progress_data *pd = (progress_data *) payload;
    pd->completed_steps = current;
    pd->total_steps = total;
    pd->path = path;
    print_progress (pd);
}

static gint acquire_credentials (git_cred **out,
                                 const gchar *url,
                                 const gchar *username_from_url,
                                 guint       allowed_types,
                                 void        *payload)
{
    gchar username[128] = {0};
    gchar password[128] = {0};

    printf("Username: ");
    scanf("%s", username);

    /* Just copyied from the libgit page, needs a little more
     * implementation ^_^ */
    printf("Password: ");
    scanf("%s", password);

    return git_cred_userpass_plaintext_new (out, username, password);
}

gint gc_clone_repository (const gchar   *url,
                          const gchar   *path)
{
    /* Check that the url and the path aren't null */
    g_assert (path != NULL);
    g_assert (url != NULL);

    /* Initialization */
    progress_data pd = {{0}};
    
    git_repository *cloned_repo = NULL;

    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
    git_checkout_opts checkout_opts = GIT_CHECKOUT_OPTS_INIT;

    gint error;

    /* Set up some options */
    checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE_CREATE;
    checkout_opts.progress_cb = checkout_progress;
    checkout_opts.progress_payload = &pd;

    clone_opts.checkout_opts = checkout_opts;
    clone_opts.fetch_progress_cb = &fetch_progress;
    clone_opts.fetch_progress_payload = &pd;
    clone_opts.cred_acquire_cb = acquire_credentials;

    // Do the clone
    error = git_clone (&cloned_repo, url, path, &clone_opts);
    
    if (error != 0)
    {
        // Oops.. We have an error
        const git_error *err = giterr_last();
        if (err) 
            printf ("ERROR %d: %s\n", err->klass, err->message);
        else 
            printf ("ERROR %d: no detailed info.\n", err->klass);
    }
    else if (cloned_repo)
        git_repository_free (cloned_repo);

    return error;
}

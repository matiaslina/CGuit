#include <gtk/gtk.h>
#include <glib.h>
#include <git2.h>
#include <string.h>

#include "guit-logview.h"
#include "git-core/common.h"

#define     FETCH_FORMAT     "net %3d%% (%4d kb, %5d/%5d) / idx %3d%% (%5d/%5d)"
#define     CHECKOUT_FORMAT  "chk %3d%% %u %u , File -> %s"

struct _progress_data 
{
    git_transfer_progress   fetch_progress;
    size_t                  completed_steps;
    size_t                  total_steps;
    const gchar             *path;
    GtkWidget               *widget;
};

typedef struct _progress_data progress_data;

static void print_progress (const progress_data *pd);
static gint fetch_progress (const git_transfer_progress *stats, void *payload);
static void checkout_progress (const gchar  *path, size_t current, size_t total,void *payload);
static gint acquire_credentials (git_cred **out, const gchar *url, const gchar *username_from_url, guint allowed_types,void *payload);
gint clone_repository (const gchar *url, const gchar *path, GtkWidget *widget);

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
        printf ("fetch progress %s\n", str_formatted);
    }
    else
    {
        gint checkout_percent = pd->total_steps > 0
                            ? (100 * pd->completed_steps) / pd->total_steps
                            : 0.f;
        sprintf (str_formatted,
                 CHECKOUT_FORMAT,
                 checkout_percent,
                 (guint) pd->completed_steps,
                 (guint) pd->total_steps,
                 pd->path);
        printf ("checkout progress %s\n", str_formatted);
    }
    
    if (pd->widget)
            guit_log_view_write_line(GUIT_LOG_VIEW (pd->widget), str_formatted);
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

gint clone_repository (const gchar   *url,
                       const gchar   *path,
                       GtkWidget     *widget)
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
    pd.widget   = widget;

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
        printf ("DEBUG CLONE FUNCTION: %s,%s\n", url, path);
        const git_error *err = giterr_last();
        if (err) 
            printf ("ERROR %d: %s\n", err->klass, err->message);
        else 
            printf ("ERROR %d: no detailed info.\n", err->klass);
            
    }
    else if (cloned_repo)
    {
        guit_log_view_write_line(GUIT_LOG_VIEW (widget), "Finished!");
        git_repository_free (cloned_repo);
    }
    return error;
}

void
set_path_from_dialog (GtkButton *button,
                      gpointer  data)
{
    GtkWidget *dir_choose_dialog;
    GtkWidget *parent_window;
    GtkEntry  *path_entry;

    path_entry = GTK_ENTRY (data);
    parent_window = gtk_widget_get_toplevel (GTK_WIDGET (path_entry));


    dir_choose_dialog = gtk_file_chooser_dialog_new ("Open folder",
                                                     GTK_WINDOW (parent_window),
                                                     GTK_FILE_CHOOSER_ACTION_OPEN,
                                                     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                     GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                     NULL);
    if (gtk_dialog_run (GTK_DIALOG (dir_choose_dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar *dirname;

        dirname = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dir_choose_dialog));
        gtk_entry_set_text (path_entry,
                            (const gchar *) dirname);

        g_free (dirname);
    }

    gtk_widget_destroy (dir_choose_dialog);
}

void
create_clone_dialog ()
{

    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *vbox;

    GtkWidget *url_label;
    GtkWidget *url;

    GtkWidget *path_label;

    GtkWidget *hbox_path;
    GtkWidget *path;
    GtkWidget *get_path_dialog;

    GtkWidget *details_label;
    GtkWidget *expander;
    GtkWidget *scroll;
    GtkWidget *logview;

    gint response;

    dialog = gtk_dialog_new_with_buttons ("Clone Repository",
                                          NULL,
                                          GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_STOCK_OK,
                                          GTK_RESPONSE_OK,
                                          GTK_STOCK_CANCEL,
                                          GTK_RESPONSE_CANCEL,
                                          NULL);
    gtk_window_set_default_size (GTK_WINDOW (dialog),
                                 460,
                                 -1);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 2);
    gtk_box_pack_start (GTK_BOX (content_area), vbox, FALSE, FALSE, 0);

    url_label = gtk_label_new_with_mnemonic ("_Url");
    url = gtk_entry_new ();

    gtk_box_pack_start (GTK_BOX (vbox), url_label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), url, FALSE, FALSE, 0);

    path_label = gtk_label_new_with_mnemonic ("_Path to save the repository");

    hbox_path = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    path = gtk_entry_new ();
    get_path_dialog = gtk_button_new_with_label ("...");
        g_signal_connect (get_path_dialog, "clicked",
                          G_CALLBACK (set_path_from_dialog), path);

    gtk_box_pack_start (GTK_BOX (hbox_path), path, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (hbox_path), get_path_dialog, FALSE, FALSE,0);

    gtk_box_pack_start (GTK_BOX (vbox), path_label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox_path, FALSE, FALSE, 0);

    /* Expander section */
    expander = gtk_expander_new ("Details");
    gtk_expander_set_resize_toplevel (GTK_EXPANDER (expander),
                                      TRUE);
    logview = guit_log_view_new ();
    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scroll),
                                    GTK_POLICY_NEVER,
                                    GTK_POLICY_ALWAYS);
    gtk_container_add (GTK_CONTAINER (scroll), logview);
    
    gtk_container_add (GTK_CONTAINER (expander), scroll);
    gtk_box_pack_start (GTK_BOX(vbox), expander, FALSE, TRUE, 0);

    gtk_widget_show_all (vbox);

    response = gtk_dialog_run (GTK_DIALOG (dialog));

    if (response == GTK_RESPONSE_OK )
    {
        // Check if the entries aren't empty
        if (strcmp (gtk_entry_get_text (GTK_ENTRY (url)), "") &&
            strcmp (gtk_entry_get_text (GTK_ENTRY (path)), ""))
        {
            // FIXME: Should use threads at this point :/
            
            clone_repository(gtk_entry_get_text (GTK_ENTRY (url)),
                             gtk_entry_get_text (GTK_ENTRY (path)),
                             logview);
        }
    }
    
    if (response == GTK_RESPONSE_CANCEL)
        gtk_widget_destroy (dialog);
}

void
guit_clone_dialog_new (GtkButton *button,
                       gpointer  *data)
{
    create_clone_dialog();
}

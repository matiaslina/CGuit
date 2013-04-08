#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

#include <assert.h>

#include "git-core.h"
#include "repository.h"

/**
 * Get the hex object id from the branch passed by parameter
 */
void hex_oid_from_file (char **uid)
{
    
    gboolean result;
    GError *err = NULL;
    char branch_file[64];
    branch_file[63] = '\0';
    
    sprintf(branch_file, "%s/.git/refs/heads/%s", gc_repository->path, 
                                                  gc_repository->branch);

    result = g_file_get_contents (branch_file,
                                  uid,
                                  NULL,
                                  &err);
                                  
    if ( !result )
    {
        g_printerr("Cannot take the HEAD uid form file %s\n", branch_file);
        g_error_free (err);
    }   
}

commit_info *gc_commit_info_new (git_commit *commit)
{
    commit_info *info;
    if((info = calloc(6,sizeof *info)) != NULL)
    {
        /* Initialize the oid */
        info->oid = malloc ( 41 * sizeof (char));
        info->oid[40] = '\0';
        const git_oid *tmp_oid = git_commit_id (commit);
        git_oid_fmt (info->oid, tmp_oid);
        
        info->message = git_commit_message (commit);
        info->author = git_commit_author (commit);
        info->committer = git_commit_committer (commit);
        info->ctime = git_commit_time (commit);
        info->parent_count = git_commit_parentcount (commit);
        info->ref_commit = commit;
    }

    return info;
}    

void gc_commit_info_free(commit_info *info)
{
    g_free (info->oid);

    git_commit_free ((git_commit *) info->ref_commit);

    info->author = NULL;
    info->committer = NULL;
   
    free(info);
    info = NULL;
}

gchar *gc_create_commit ( const gchar *author_name,
                          const gchar *author_email,
                          const gchar *committer_name,
                          const gchar *committer_email,
                          gchar *message,
                          gchar *encoding,
                          const git_tree *tree,
                          const git_commit *parent,
                          int parent_count)
{
    static char out[41];
    git_oid commit_id;
    git_signature *author, *committer;

    git_signature_now ((git_signature **) &author,
                       author_name, author_email);
    git_signature_now ((git_signature **) &committer,
                       committer_name,
                       committer_email);

    git_commit_create_v( &commit_id,                  // out id
                         gc_current_repository, // Repository
                         NULL,                        // (update_ref) do not update the ref
                         author,                      // Author of the commit
                         committer,                   // Committer 
                         encoding,                    // Encoding
                         message,                     // Message
                         tree,                        // Parent tree
                         1,                           // parent count
                         parent);                     // List the parents, we can have a lot of here.

    /* Free all the signatures */
    git_signature_free (author);
    git_signature_free (committer);
    git_oid_fmt (out, &commit_id);

    return out;
}

GList *gc_all_commits ()
{
    static GList *list = NULL;

    gchar *hex_oid;

    git_oid oid;
    git_commit *commit;
    git_revwalk *walker;
    gint error = 0;

    hex_oid_from_file (&hex_oid);

    git_oid_fromstr (&oid, hex_oid);
        
    git_revwalk_new (&walker, gc_repository->current);
    git_revwalk_sorting (walker, GIT_SORT_TOPOLOGICAL);
    git_revwalk_push (walker, &oid);

    while ((git_revwalk_next(&oid, walker)) == 0)
    {
        error = git_commit_lookup (&commit, gc_repository->current, &oid);
        
        if (error != 0)
            goto lookup_error;
        
        commit_info *info = gc_commit_info_new (commit);
        
        list = g_list_append (list, info);
    }

    git_revwalk_free (walker);
    list = g_list_first (list);

    return list;

lookup_error:
    git_revwalk_free (walker);

    g_list_foreach (list, (GFunc) gc_commit_info_free, NULL);
    if (commit != NULL)
    {
        git_commit_free (commit);
        commit = NULL;
    }
    g_list_free (list);
    return NULL;
}

void
gc_nth_tree (git_tree *tree,
                   unsigned int depth,
                   const char *branch)
{}



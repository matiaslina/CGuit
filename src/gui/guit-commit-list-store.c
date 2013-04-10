#include <gtk/gtk.h>
#include <git2.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../git-core/common.h"
#include "guit-commit-list-store.h"


column_info *
column_info_new_from_commit (git_commit *commit)
{
    column_info *info = NULL;

    if ((info = calloc (4, sizeof *info)) != NULL)
    {

        time_t time;
        git_oid *tmp_oid;
        gchar oid_str[41];
        git_signature *signature;

        /* Message */
        //info->message = (gchar *) git_commit_message (commit);
        info->message = "Prueba :D";

        /* Signature of the commit, name and email from the author. */
        info->author[31] = '\0';
        signature = (git_signature *)git_commit_author (commit);
        
        sprintf (info->author, "%s<%s>",
                 signature->name,
                 signature->email);

        /* get the time in the format dd/mm/yyyy 
         * (sort of) */
        time = git_commit_time (commit);
        struct tm *tl = localtime (&time);

        info->date[15] = '\0';
        sprintf (info->date, "%d/%d/%d",
                 tl->tm_mday,
                 tl->tm_mon + 1,
                 tl->tm_year + 1900);

        /* first 7 characteres from the hash of the commit */
        info->oid[7] = '\0';
        oid_str[40] = '\0';
        tmp_oid = (git_oid *) git_commit_id (commit);
        git_oid_fmt (oid_str, tmp_oid);
        strncpy (info->oid, oid_str, 7);
        

        //git_signature_free (signature);
    }
    else
        g_warning ("Cannot allocate memory for column_info\nReturning NULL");

    return info;
}

GtkTreeModel *
guit_commit_list_store_new (void) 
{
    GtkListStore    *store;
    GtkTreeIter     iter;

    store = gtk_list_store_new (COMMIT_LIST_STORE_NUM_COLUMNS,
                                G_TYPE_STRING,
                                G_TYPE_STRING,
                                G_TYPE_STRING,
                                G_TYPE_STRING);

    git_revwalk     *walk;
    gint            error = 0;
    git_oid         *oid;
    git_commit      *commit;

    column_info     *info;
    

    oid = (git_oid *) git_reference_target (git->reference);

    git_revwalk_new (&walk, git->repository);
    git_revwalk_sorting (walk, GIT_SORT_TOPOLOGICAL);
    git_revwalk_push (walk, oid);

    while ((git_revwalk_next (oid, walk)) == 0)
    {
        error = git_commit_lookup (&commit, git->repository, oid);

        if (error != 0)
            g_warning ("Error while lookup for a commit in guit_commit_list_store_new at line 95");
        
        info = column_info_new_from_commit (commit);

        guit_commit_list_store_append (info, store);
#if 0
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter,
                            COMMIT_LIST_STORE_MESSAGE, info->message,
                            COMMIT_LIST_STORE_DATE, info->date,
                            COMMIT_LIST_STORE_AUTHOR, info->author,
                            COMMIT_LIST_STORE_COMMIT_ID, info->oid,
                            -1);
#endif
        free (info);
        git_commit_free (commit);
    }

    git_revwalk_free (walk);

    return GTK_TREE_MODEL (store);
}

void 
guit_commit_list_store_append (column_info      *info,
                               GtkListStore     *store)
{
    GtkTreeIter iter;

    gtk_tree_model_get_iter_first (GTK_TREE_MODEL (store), &iter);

    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
                        COMMIT_LIST_STORE_MESSAGE, info->message,
                        COMMIT_LIST_STORE_DATE, info->date,
                        COMMIT_LIST_STORE_AUTHOR, info->author,
                        COMMIT_LIST_STORE_COMMIT_ID, info->oid,
                        -1);
}
void
guit_commit_list_store_add_columns (GtkTreeView *treeview)
{    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeModel *model = gtk_tree_view_get_model (treeview);
    
    /* The messages column */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Message",
                                                       renderer,
                                                       "text",
                                                       COMMIT_LIST_STORE_MESSAGE,
                                                       NULL);
    gtk_tree_view_append_column (treeview, column);
    
    /* Date column */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Date",
                                                       renderer,
                                                       "text",
                                                       COMMIT_LIST_STORE_DATE,
                                                       NULL);
    gtk_tree_view_column_set_sort_column_id (column, COMMIT_LIST_STORE_DATE);
    gtk_tree_view_append_column (treeview, column);
    
    /* The Author column */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Author",
                                                       renderer,
                                                       "text",
                                                       COMMIT_LIST_STORE_AUTHOR,
                                                       NULL);
    gtk_tree_view_append_column (treeview, column);
    
    /* The commit column */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Commit",
                                                       renderer,
                                                       "text",
                                                       COMMIT_LIST_STORE_COMMIT_ID,
                                                       NULL);
    gtk_tree_view_append_column (treeview, column);
}

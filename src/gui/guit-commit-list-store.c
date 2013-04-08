#include <gtk/gtk.h>
#include <time.h>
#include <string.h>

#include "../git-core/git-core.h"

#include "guit-commit-list-store.h"

GtkTreeModel *
guit_commit_list_store_new (void)
{
    
    GtkListStore *store;
    GtkTreeIter iter;
    
    /* Create a list store */
    store = gtk_list_store_new (COMMIT_LIST_STORE_NUM_COLUMNS,
                                G_TYPE_STRING,
                                G_TYPE_STRING,
                                G_TYPE_STRING,
                                G_TYPE_STRING);
                                
    GList *commit_list = gc_all_commits ();
    GList *it;
    
    for (it = commit_list; it != NULL; it = it->next)
    {
        commit_info *info = (commit_info *) it->data;
        gchar   date[16];
        gchar   short_commit_oid[8];
        gchar   author[128];
        
        date[15] = '\0';
        time_t t = info->ctime;
        struct tm *lt = localtime (&t);
        
        short_commit_oid[7] = '\0';
        strncpy (short_commit_oid, info->oid, 7);
        
        sprintf (date, "%d/%d/%d",
                 lt->tm_mday,           // day
                 lt->tm_mon + 1,        // month
                 lt->tm_year + 1900);   // year
                 
        author[127] = '\0';
        sprintf (author, "%s <%s>",
                 info->author->name,
                 info->author->email);
        
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter,
                            COMMIT_LIST_STORE_MESSAGE, info->message,
                            COMMIT_LIST_STORE_DATE, date,
                            COMMIT_LIST_STORE_AUTHOR, author,
                            COMMIT_LIST_STORE_COMMIT_ID, short_commit_oid,
                            -1);
    }

    g_list_foreach (commit_list, (GFunc) gc_commit_info_free, NULL);
    g_list_free (commit_list);
    
    return GTK_TREE_MODEL (store);
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


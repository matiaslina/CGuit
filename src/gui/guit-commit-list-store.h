#ifndef _GUIT_COMMIT_LIST_STORE_H_
#define _GUIT_COMMIT_LIST_STORE_H_

#include <gtk/gtk.h>

enum {
    
    COMMIT_LIST_STORE_MESSAGE,
    COMMIT_LIST_STORE_DATE,
    COMMIT_LIST_STORE_AUTHOR,
    COMMIT_LIST_STORE_COMMIT_ID,
    COMMIT_LIST_STORE_NUM_COLUMNS
};

void guit_commit_list_store_add_columns (GtkTreeView *treeview);

GtkTreeModel *guit_commit_list_store_new (void);

#endif

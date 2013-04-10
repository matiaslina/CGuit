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

struct _column_info {
    gchar   *message;
    gchar   author[32];
    gchar   date[16];
    gchar   oid[8];
};

typedef struct _column_info column_info;


GtkTreeModel *guit_commit_list_store_new (void);

void guit_commit_list_store_append (column_info *info, GtkListStore *store);

void guit_commit_list_store_add_columns (GtkTreeView *treeview);

#endif

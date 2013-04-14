#ifndef _GIT_CORE_CLONE_H_
#define _GIT_CORE_CLONE_H_

#include <git2.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "common.h"

struct _progress_data 
{
    git_transfer_progress   fetch_progress;
    size_t                  completed_steps;
    size_t                  total_steps;
    const gchar             *path;
    GCPrintFunc             print_cb;
    GtkWidget               *widget;
};

typedef struct _progress_data progress_data;

gint    gc_clone_repository (const gchar *url,const gchar *path, GCPrintFunc func, GtkWidget *widget);

#endif

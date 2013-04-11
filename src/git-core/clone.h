#ifndef _GIT_CORE_CLONE_H_
#define _GIT_CORE_CLONE_H_

#include <git2.h>
#include <glib.h>

enum {
    CLONE_SIGNAL_FETCH_DATA,
    CLONE_SIGNAL_CHECKOUT_DATA,
    CLONE_SIGNAL_NUM,
};

static guint clone_signals[CLONE_SIGNAL_NUM] = {0};

struct _progress_data 
{
    git_transfer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const gchar *path;
};

typedef struct _progress_data progress_data;

gint    gc_clone_repository (const gchar *url,const gchar *path);

#endif

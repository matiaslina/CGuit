#ifndef _GIT_CORE_CLONE_H_
#define _GIT_CORE_CLONE_H_

#include <git2.h>
#include <glib.h>

struct _progress_data 
{
    git_transfer_progress fetch_progress;
    size_t completed_steps;
    size_t total_steps;
    const gchar *path;
};

typedef struct _progress_data progress_data;

gint    gc_clone_repository (gchar *url, gchar *path);

#endif

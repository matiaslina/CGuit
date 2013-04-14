#ifndef _GIT_CORE_COMMON_H_
#define _GIT_CORE_COMMON_H_

#include "git2.h"
#include <glib.h>
#include <gtk/gtk.h>

/* Some errors */
enum {
    GC_GIT_DATA_INIT_OK,
    GC_REPOSITORY_UNINIT,
    GC_REFERENCE_UNINIT,
};

typedef struct {
    git_repository  *repository;
    git_reference   *reference;
} GitData;

/**
 * Callback for printing some things
 * I belive that only its needed a GuitLogView here.
 */
typedef void (*GCPrintFunc) (GtkWidget *widget, gchar *str);

GitData *git;

/**
 * Initialize the GitData struct initializing 
 * the repository and the reference (branch I guess)
 */
gint gc_git_data_init (gchar *path);

void gc_git_data_change_dir (gchar *path);

void gc_git_data_update_ref (void);

void gc_git_data_free (void);



#endif

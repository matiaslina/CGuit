#include <git2.h>
#include <glib.h>
#include "common.h"

gint gc_git_data_init (gchar *path)
{
    gint error;
    // Not implemented
    if ((git = calloc (2, sizeof *git)) != NULL)
    {
        error = git_repository_open (&git->repository, path);
        if (error != 0)
            return GC_REPOSITORY_UNINIT;

        error = git_repository_head (&git->reference, git->repository);
        if (error != 0)
            return GC_REFERENCE_UNINIT;
    }

    return GC_GIT_DATA_INIT_OK;
}
void gc_git_data_change_dir (gchar *path)
{
    // Not implemented
}

void gc_git_data_update_ref ()
{
    // Not implemented
}

void gc_git_data_free ()
{
    git_repository_free (git->repository);
    git->repository = NULL;

    git_reference_free (git->reference);
    git->reference = NULL;

    g_free (git);
}

#include <git2.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "repository.h"

extern GCRepository *gc_repository;

void gc_repository_init (char *path,
                         char *branch)
{
   if ((gc_repository = calloc(3, sizeof (*gc_repository))) != NULL)
   {
       git_repository_open (&gc_repository->current, path);
       gc_repository->branch = branch;
       gc_repository->path = path;
   }

   g_assert(gc_repository != NULL);
}

void gc_repository_free (void)
{
    if (gc_repository != NULL)
    {
        git_repository_free (gc_repository->current);
        g_free (gc_repository);
        gc_repository = NULL;
    }
    else
        g_warning ("Cannot free gc_repository: The repository is NULL");
}

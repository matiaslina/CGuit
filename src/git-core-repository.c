#include <git2.h>
#include <glib.h>
#include <glib/gstdio.h>


extern GCRepository *gc_repository;
gc_repository = NULL;

void gc_repository_init (char *path,
                         char *branch)
{
   if (gc_repository = malloc(sizeof (GCRepository)) != NULL)
   {
       git_repository_open (&(gc_repository->current), path);
       gc_repository->branch = branch;
       gc_repository->path = path;
   }

   g_assert(gc_repository != NULL);
}

void gc_repository_free (void)
{
    git_repository_free (gc_repository->current);
    free (gc_repository);
    gc_repository = NULL;
}

#ifndef _GIT_CORE_REPOSITORY_H_
#define _GIT_CORE_REPOSITORY_H_

#include <git2.h>

typedef struct {
    git_repository  *current;
    char            *branch;
    char            *path;
} GCRepository;

GCRepository *gc_repository;

void gc_repository_init (char *path, char *branch);

void gc_repository_free (void);

#endif

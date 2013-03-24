#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

void git_core_load_repository (const gchar *path);

git_repository* git_core_current_repository;

typedef struct {
    const git_signature *author, *committer;
    const char *message;
    time_t ctime;
    unsigned int parent_count;
} commit_info;

commit_info *git_core_commit_info_new (git_commit *commit);

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

/**
 * git_core_commit_info_new
 * Create a struct with all the data of one commit.
 * it includes:
 *        * author
 *        * committer
 *        * message
 *        * time of the commit
 *        * the count of the parens
 * 
 * @return commit_info pointer
 * NOTE: Don't know if it's necessary to free the commit
 */
commit_info *git_core_commit_info_new (git_commit *commit);

/**
 * git_core_create_commit
 *
 * Do a commit on the actual repository.
 */
gchar *git_core_create_commit ( const gchar *author_name,
                                const gchar *author_email,
                                const gchar *committer_name,
                                const gchar *committer_email,
                                gchar *message,
                                gchar *encoding,
                                const git_tree *tree,
                                const git_commit *parent,
                                int parent_count);

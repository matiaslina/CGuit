#ifndef _GIT_CORE_H
#define _GIT_CORE_H

#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

void gc_load_repository (const gchar *path);

git_repository* gc_current_repository;

typedef struct {
    char                    *oid;
    const git_signature     *author;
    const git_signature     *committer;
    const char              *message;
    time_t                  ctime;
    unsigned int            parent_count;
    git_commit              *ref_commit;
} commit_info;

typedef struct {
    char *parent_dir;
    char *name;
    gboolean is_dir;
} gc_file_info;

void hex_oid_from_file (char **uid);

/**
 * gc_commit_info_new
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
commit_info *gc_commit_info_new (git_commit *commit);

/**
 * gc_commit_info_free
 * Frees a commit_info struct
 */
void gc_commit_info_free(commit_info *info);

/**
 * gc_create_commit
 *
 * Do a commit on the actual repository.
 */
gchar *gc_create_commit (const gchar *author_name,
                         const gchar *author_email,
                         const gchar *committer_name,
                         const gchar *committer_email,
                         gchar *message,
                         gchar *encoding,
                         const git_tree *tree,
                         const git_commit *parent,
                         int parent_count);
/**
 * gc_all_commits
 *
 * Get a list with all commits on a branch.
 */
GList *gc_all_commits ();

/**
 * gc_nth_tree
 *
 * get the nth tree from the branch passed bt parameter.
 * NOTE: NOT IMPLEMENTED YET.
 */
void gc_nth_tree (git_tree *tree,
                        unsigned int depth,
                        const char *branch);

#endif

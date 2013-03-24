#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "git-core.h"

extern git_repository* git_core_current_repository;
git_repository* git_core_current_repository = NULL;

static void get_hex_oid (gchar **uid, gchar *branch_file)
{
    gboolean result;
    GError *err = NULL;
    
    result = g_file_get_contents (branch_file,
                                  uid,
                                  NULL,
                                  &err);
                                  
    if ( !result )
    {
        g_printerr("Cannot take the HEAD uid form file %s\n", branch_file);
        g_error_free (err);
    }
    
}

commit_info *git_core_commit_info_new (git_commit *commit)
{
	commit_info *info;
	if((info = malloc(sizeof *info)) != NULL)
	{
		info->author = git_commit_author (commit);
		info->message = git_commit_message (commit);
		info->author = git_commit_author (commit);
		info->committer = git_commit_committer (commit);
		info->ctime = git_commit_time (commit);

		info->parent_count = git_commit_parentcount (commit);
	}

	return info;
}	

void git_core_load_repository (const gchar *path)
{
    g_return_if_fail (path != NULL);
    git_repository_open (&git_core_current_repository, path);
}

int main (int argc, char **argv)
{
    gchar *uid;
    const char *repo_path = ".";
    gchar *path_to_branch_file = "./.git/refs/heads/master";
    git_core_load_repository (repo_path);
    
    
    get_hex_oid (&uid, path_to_branch_file);
    
    git_oid oid;
    git_oid_fromstr (&oid, uid);
    g_free(uid);
    
    git_commit *commit;
    git_commit_lookup (&commit, git_core_current_repository, &oid);
    
	commit_info *info = git_core_commit_info_new (commit);
    
    printf("Author: %s (%s)\n", info->author->name, info->author->email);
    
    git_commit_free (commit);
    
	
    git_repository_free (git_core_current_repository);
    return 0;
}

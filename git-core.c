#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "git-core.h"

extern git_repository* git_core_current_repository;

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

gchar *git_core_create_commit ( const gchar *author_name,
								const gchar *author_email,
								const gchar *committer_name,
								const gchar *committer_email,
								gchar *message,
								gchar *encoding,
								const git_tree *tree,
								const git_commit *parent,
								int parent_count)
{
	static char out[41];
	git_oid commit_id;
	git_signature *author, *committer;

	git_signature_now ((git_signature **) &author,
					   author_name, author_email);
	git_signature_now ((git_signature **) &committer,
					   committer_name,
					   committer_email);

	git_commit_create_v( &commit_id,                  // out id
						 git_core_current_repository, // Repository
						 NULL,                        // (update_ref) do not update the ref
						 author,                      // Author of the commit
						 committer,                   // Committer 
						 encoding,                    // Encoding
						 message,                     // Message
						 tree,                        // Parent tree
						 1,                           // parent count
						 parent);                     // List the parents, we can have a lot of here.

	/* Free all the signatures */
	git_signature_free (author);
	git_signature_free (committer);
	git_oid_fmt (out, &commit_id);

	return out;
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

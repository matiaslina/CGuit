#include <git2.h>

#include "git-core.h"
#include "git-core-repository.h"

int main (int argc, char **argv)
{
    gchar *uid;
    gchar *repo_path = ".";
    gchar *branch = "master";
    
    gc_repository_init(repo_path, branch);
    
    hex_oid_from_file (&uid);
    
    git_oid oid;
    git_oid_fromstr (&oid, uid);
    
    g_free(uid);
    
    git_commit *commit;
    git_commit_lookup (&commit, gc_repository->current, &oid);
    
    commit_info *info = gc_commit_info_new (commit);
    
    printf("Author: %s (%s)\n", info->author->name, info->author->email);
    
    gc_commit_info_free(info);
    
    git_commit_free (commit);

    GList *all_commit_list = gc_all_commits ();
    GList *it;

    for ( it = all_commit_list; it != NULL; it = it->next)
    {
        info = (commit_info *) it->data;

        printf("Message-> %s\n", info->message);
    }

    //printf("Author: %s\n", my_info->author->name);
    
    /* Freeing the list */
    g_list_free_full (all_commit_list, (GDestroyNotify) gc_commit_info_free);
    g_list_free(all_commit_list);
    
    gc_repository_free();
    return 0;
}

/*
int main (int argc, char **argv)
{
    gchar *uid;
    const char *repo_path = ".";
    gchar *path_to_branch_file = "./.git/refs/heads/master";
    gc_load_repository (repo_path);
    
    
    get_hex_oid (&uid, path_to_branch_file);
    
    git_oid oid;
    git_oid_fromstr (&oid, uid);
    g_free(uid);
    
    git_commit *commit;
    git_commit_lookup (&commit, gc_current_repository, &oid);
    
    commit_info *info = gc_commit_info_new (commit);
    
    printf("Author: %s (%s)\n", info->author->name, info->author->email);
    
    git_commit_free (commit);

    GList *all_commit_list = gc_all_commits (path_to_branch_file);
    GList *it;

    for ( it = all_commit_list; it != NULL; it = it->next)
    {
        info = (commit_info *) it->data;

        printf("Message-> %s\n", info->message);
    }

    //printf("Author: %s\n", my_info->author->name);
    
    Freeing the list 
    g_list_free_full (all_commit_list, (GDestroyNotify) gc_commit_info_free);
    g_list_free(all_commit_list);
    
    
    git_repository_free (gc_current_repository);
    return 0;
}
*/

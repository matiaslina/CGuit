#include <git2.h>
#include <stdio.h>
#include "common.h"

void 
revwalk_test (void)
{
    gint error;
    git_reference *reference;

    git_repository_head (&reference, git->repository);
    
    const gchar *name = git_reference_name ((const git_reference *) reference);

    printf ("reference name -> %s\n", name);

    if (git_reference_has_log( reference))
        printf ("tiene logs!\n");
    if (git_reference_is_branch (reference))
    {
        printf ("Es un branch!\n");
    }
    if (git_reference_is_remote (reference))
        printf (":o encima es remota!\n");


    git_reflog *reflog;
    git_reflog_read (&reflog, reference);
    
    size_t entry_count = git_reflog_entrycount (reflog);
    gint i;
    for (i = 0; i < (gint) entry_count ; i++)
    {
        const git_reflog_entry *entry = git_reflog_entry_byindex (reflog, i);
        printf ("Git reflog message -> %s\n", git_reflog_entry_message (entry));
    }
    git_reflog_free (reflog);

    git_reference_free (reference);


}

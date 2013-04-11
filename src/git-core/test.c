#include <git2.h>
#include <stdio.h>
#include <glib.h>
#include "common.h"

void 
revwalk_test (void)
{
    unsigned int ecount;
    int i;
    git_index *index;
    gchar out[41];
    out[40] = '\0';

    git_repository_index (&index, git->repository);

    git_index_read (index);

    ecount = git_index_entrycount (index);
    if (!ecount)
        printf ("Empty index\n");

    for (i = 0; i < ecount; ++i)
    {
        const git_index_entry *e = git_index_get_byindex (index, i);

        git_oid_fmt (out, &e->oid);

        printf("File Path: %s\n", e->path);
        printf("    Stage: %d\n", git_index_entry_stage(e));
        printf(" Blob SHA: %s\n", out);
        printf("File Mode: %07o\n", e->mode);
        printf("File Size: %d bytes\n", (int)e->file_size);
        printf("Dev/Inode: %d/%d\n", (int)e->dev, (int)e->ino);
        printf("  UID/GID: %d/%d\n", (int)e->uid, (int)e->gid);
        printf("    ctime: %d\n", (int)e->ctime.seconds);
        printf("    mtime: %d\n", (int)e->mtime.seconds);
        printf("\n");
    }


    git_index_free (index);
}

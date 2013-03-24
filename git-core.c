#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>


static gboolean get_uid (gchar **uid, gchar *branch_file)
{
    gboolean result;
    GError *err = NULL;
    
    result = g_file_get_contents (branch_file,
                                  uid,
                                  NULL,
                                  &err);
                                  
    if ( !result )
    {
        g_error_free (err);
        return FALSE;
    }
    
    
    return TRUE;
}


int main (int argc, char **argv)
{
    gchar *uid;
    
    gchar *path_to_branch_file = "./.git/refs/heads/master";
    
    gboolean err;
    
    err = get_uid (&uid, path_to_branch_file);
    
    if (! err){
        printf("Hubo un error\n");
        return 1;
    }
    printf("uid -> %s\n", uid);
    g_free(uid);
    
    return 0;
}

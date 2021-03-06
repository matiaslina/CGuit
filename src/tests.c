#include <gtk/gtk.h>

#include "git-core/common.h"
#include "guit-commit-list-store.h"
#include "guit-logview.h"
#include "guit-clone-init-dialog.h"
#include "guit-toolbar.h"

int main (int argc, char **argv)
{
    gc_git_data_init (".");
    
    /* Initialize the threads */

    gtk_init (&argc, &argv);
    
    
    GtkWidget *window;
    GtkWidget *vbox;
    
    GtkWidget *toolbar;
        
    GtkWidget *logview;
    GtkWidget *scrolled;
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title (GTK_WINDOW (window), "CGuit test");
    g_signal_connect (window,"destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
        
    toolbar = guit_toolbar_new();
    gtk_box_pack_start (GTK_BOX (vbox), toolbar, FALSE, FALSE, 3);
        
    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled),
                                         GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    
    logview = guit_log_view_new ();
    guit_log_view_write_line (GUIT_LOG_VIEW (logview), "Initialized");
    
    
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 280);
    gtk_box_pack_start (GTK_BOX (vbox), scrolled, TRUE, TRUE, 0);
    
    gtk_container_add (GTK_CONTAINER (scrolled), logview);
    
    gtk_widget_show_all (window);

    gtk_main ();

    gc_git_data_free ();
    return 0;
}

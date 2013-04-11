#include <gtk/gtk.h>

#include "git-core/common.h"
#include "./gui/guit-commit-list-store.h"
#include "gui/guit-new-commit-dialog.h"
#include "gui/guit-clone-dialog.h"

int main (int argc, char **argv)
{
    gc_git_data_init (".");

    gtk_init (NULL, NULL);
    
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    
    GtkWidget *new_commit_btn;
    
    GtkWidget *treeview;
    GtkWidget *scrolled;
    GtkTreeModel *model;
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title (GTK_WINDOW (window), "CGuit");
    g_signal_connect (window,"destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 9);
    
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    
    label = gtk_label_new ("Commit list store test");
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    
    new_commit_btn = gtk_button_new_with_mnemonic ("_Clone Repository");
    g_signal_connect (new_commit_btn, "clicked",
                      G_CALLBACK (guit_clone_dialog_new),
                      NULL);
    gtk_box_pack_start (GTK_BOX (vbox), new_commit_btn, FALSE, FALSE, 0);
    
    
    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled),
                                         GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    //printf ("a\n");
    model = guit_commit_list_store_new ();
    
    treeview = gtk_tree_view_new_with_model (model);
    g_object_unref (model);

    gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (treeview), TRUE);

    guit_commit_list_store_add_columns (GTK_TREE_VIEW (treeview));
    
    
    
    
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 280);
    gtk_box_pack_start (GTK_BOX (vbox), scrolled, TRUE, TRUE, 0);
    
    gtk_container_add (GTK_CONTAINER (scrolled), treeview);
    
    gtk_widget_show_all (window);
    gtk_main ();

    gc_git_data_free ();
    return 0;
}

#include <gtk/gtk.h>

#if     0
static gint
on_response_ok (GtkButton *button,
                gpointer data)
{
    const gchar *author = "Matias Linares";
    const gchar *author_email = "matiaslina@gmail.com";
    const gchar *committer = "Matias Linares";
    const gchar *committer_email = "matiaslina@gmail.com";
    
    gchar *message = (gchar *) data;
    
    gchar *gc_create_commit (author_name,
                         author_email,
                         committer_name,
                         committer_email,
                         message,
                         NULL,
                         tree,
                         parent,
                         1);
}
#endif
void 
guit_new_commit_dialog_new (GtkButton *button,
                            gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *vbox;
    
    GtkWidget *label;
    GtkWidget *message;
    
    gint response;
    
    dialog = gtk_dialog_new_with_buttons ("New Commit",
                                          NULL, //window
                                          GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_STOCK_OK,
                                          GTK_RESPONSE_OK,
                                          GTK_STOCK_CANCEL,
                                          GTK_RESPONSE_CANCEL,
                                          NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 2);
    gtk_box_pack_start (GTK_BOX (content_area), vbox, FALSE, FALSE, 0);
    
    label = gtk_label_new_with_mnemonic ("_Message");
    message = gtk_entry_new();
    
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 1);
    gtk_box_pack_start (GTK_BOX (vbox), message, FALSE, FALSE, 1);
    
    gtk_widget_show_all (vbox);
    
    response = gtk_dialog_run (GTK_DIALOG (dialog));
    
    if (response == GTK_RESPONSE_OK)
        printf("DIALOG -> OK\n");
            
    gtk_widget_destroy (dialog);
}

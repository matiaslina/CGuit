#include <gtk/gtk.h>
#include <glib.h>
#include <git2.h>
#include "../git-core/clone.h"
#include "../git-core/common.h"

void
on_response (gint response)
{
    // Not implemented yet
}

void
set_path_from_dialog (GtkButton *button,
                      gpointer  data)
{
    GtkWidget *dir_choose_dialog;
    GtkWidget *parent_window;
    GtkEntry  *path_entry;

    path_entry = GTK_ENTRY (data);
    parent_window = gtk_widget_get_toplevel (GTK_WIDGET (path_entry));


    dir_choose_dialog = gtk_file_chooser_dialog_new ("Open folder",
                                                     GTK_WINDOW (parent_window),
                                                     GTK_FILE_CHOOSER_ACTION_OPEN,
                                                     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                     GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                     NULL);
    if (gtk_dialog_run (GTK_DIALOG (dir_choose_dialog)) == GTK_RESPONSE_ACCEPT)
    {
        gchar *dirname;

        dirname = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dir_choose_dialog));
        gtk_entry_set_text (path_entry,
                            (const gchar *) dirname);

        g_free (dirname);
    }

    gtk_widget_destroy (dir_choose_dialog);
}

void
create_clone_dialog ()
{

    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *vbox;

    GtkWidget *url_label;
    GtkWidget *url;

    GtkWidget *path_label;

    GtkWidget *hbox_path;
    GtkWidget *path;
    GtkWidget *get_path_dialog;

    gint response;

    dialog = gtk_dialog_new_with_buttons ("Clone Repository",
                                          NULL,
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

    url_label = gtk_label_new_with_mnemonic ("_Url");
    url = gtk_entry_new ();

    gtk_box_pack_start (GTK_BOX (vbox), url_label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), url, FALSE, FALSE, 0);

    path_label = gtk_label_new_with_mnemonic ("_Path to save the repository");

    hbox_path = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    path = gtk_entry_new ();
    get_path_dialog = gtk_button_new_with_label ("...");
        g_signal_connect (get_path_dialog, "clicked",
                          G_CALLBACK (set_path_from_dialog), path);

    gtk_box_pack_start (GTK_BOX (hbox_path), path, FALSE, FALSE,0);
    gtk_box_pack_start (GTK_BOX (hbox_path), get_path_dialog, FALSE, FALSE,0);


    gtk_box_pack_start (GTK_BOX (vbox), path_label, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox_path, FALSE, FALSE, 0);

    gtk_widget_show_all (vbox);

    response = gtk_dialog_run (GTK_DIALOG (dialog));

    on_response (response);
    
    gtk_widget_destroy (dialog);
}

void
guit_clone_dialog_new (GtkButton *button,
                       gpointer  *data)
{
    create_clone_dialog();
}

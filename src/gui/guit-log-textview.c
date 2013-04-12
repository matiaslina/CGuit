#include <gtk/gtk.h>
#include <glib.h>
#include "guit-log-textview.h"

GtkWidget *
guit_log_textview_init ()
{
    GtkWidget *view;
    GtkTextBuffer *buffer;

    PangoFontDescription *font_desc;
    GdkColor color;

    view = gtk_text_view_new ();
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    gtk_text_buffer_set_text (buffer, "", -1);

    /* Change the default font of the widget */
    font_desc = pango_font_description_from_string ("Monospace 10");
    gtk_widget_modify_font (view, font_desc);
    pango_font_description_free (font_desc);

    gdk_color_parse ("white", &color);
    gtk_widget_modify_fg (view, GTK_STATE_NORMAL, &color);

    gdk_color_parse ("black", &color);
    gtk_widget_modify_bg (view, GTK_STATE_NORMAL, &color);

    guit_log_textview_write_line (GTK_TEXT_VIEW (view), "Initialized log view...");
    guit_log_textview_write_line (GTK_TEXT_VIEW (view), "This is just another line...");

    return view;
}

void 
guit_log_textview_write_line (GtkTextView *view,
                              gchar *line)
{
    GtkTextBuffer *buffer;
    GtkTextIter   iter;
    gchar         new_line[1025];
    
    new_line[1024] = '\0';
    
    sprintf (new_line, "%s\n", line);
    
    

    buffer = gtk_text_view_get_buffer (view);
    //gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert (buffer, &iter, new_line, -1);
}

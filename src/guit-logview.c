#include <gtk/gtk.h>
#include <glib.h>
#include "guit-logview.h"

/* Macros */
static void guit_log_view_class_init (GuitLogViewClass *klass);
static void guit_log_view_init (GuitLogView *logview);

/**
 * Class Constructor
 */
static void
guit_log_view_class_init (GuitLogViewClass *klass)
{
}

/**
 * Instance Constructor
 */
static void
guit_log_view_init (GuitLogView *logview)
{
    // Initializations
    GtkWidget *view;
    GtkTextBuffer *buffer;
    PangoFontDescription *font_desc;
    GdkColor color;

    // Get the buffer and set an empty line.
    view = (GtkWidget *) logview;
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    gtk_text_buffer_set_text (buffer, "", -1);

    /* Change the default font of the widget */
    font_desc = pango_font_description_from_string ("Monospace 9");
    gtk_widget_modify_font (view, font_desc);
    pango_font_description_free (font_desc);

    gdk_color_parse ("white", &color);
    gtk_widget_modify_fg (view, GTK_STATE_NORMAL, &color);

    gdk_color_parse ("black", &color);
    gtk_widget_modify_bg (view, GTK_STATE_NORMAL, &color);

    // set non editable
    gtk_text_view_set_editable (GTK_TEXT_VIEW (view), TRUE);
}


GType guit_log_view_get_type (void)
{
    static GType log_view_type = 0;

    if (! log_view_type)
    {
        GTypeInfo log_view_info =
        {
            sizeof (GuitLogViewClass),
            NULL,
            NULL,
            (GClassInitFunc) guit_log_view_class_init,
            NULL,
            NULL,
            sizeof (GuitLogView),
            0,
            (GInstanceInitFunc) guit_log_view_init
        };

        log_view_type = g_type_register_static (GTK_TYPE_TEXT_VIEW,
                                                "GuitLogView",
                                                &log_view_info,
                                                0);
    }

    return log_view_type;
}

GtkWidget *
guit_log_view_new ()
{
    return GTK_WIDGET (g_object_new (GUIT_LOG_VIEW_TYPE, NULL));
}

void 
guit_log_view_write_line (GuitLogView *view,
                              gchar *line)
{
    GtkTextBuffer *buffer;
    GtkTextIter   iter;
    gchar         new_line[1025];
    
    new_line[1024] = '\0';
    
    sprintf (new_line, "%s\n", line);
    
    

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
    //gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert (buffer, &iter, new_line, -1);
}

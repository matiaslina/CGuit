#include <gtk/gtk.h>
#include <glib.h>
#include "guit-toolbar.h"
#include "guit-clone-init-dialog.h"

static void guit_toolbar_class_init (GuitToolbarClass *klass);
static void guit_toolbar_init (GuitToolbar *toolbar);
void clone_repository_cb (GtkWidget *widget, gpointer data);

GType 
guit_toolbar_get_type ()
{
    static GType toolbar_type = 0;
    if (! toolbar_type)
    {
        GTypeInfo toolbar_info = {
            sizeof (GuitToolbarClass),
            NULL,
            NULL,
            (GClassInitFunc) guit_toolbar_class_init,
            NULL,
            NULL,
            sizeof (GuitToolbar),
            0,
            (GInstanceInitFunc) guit_toolbar_init
        };
        
        toolbar_type = g_type_register_static (GTK_TYPE_TOOLBAR,
                                               "GuitToolbar",
                                               &toolbar_info,
                                               0);
    }
    
    return toolbar_type;
}

static void
guit_toolbar_class_init (GuitToolbarClass *klass){};

static void guit_toolbar_init (GuitToolbar *toolbar)
{
    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar),
                           GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width (GTK_CONTAINER (toolbar), 2);
    
    /* FIXME: encontrar un icono para el clonado de repositorio. */
    toolbar->clone = gtk_tool_button_new_from_stock (GTK_STOCK_UNDO);
    gtk_widget_set_name (GTK_WIDGET (toolbar->clone), "clone");
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), toolbar->clone, -1);
    g_signal_connect (G_OBJECT (toolbar->clone), "clicked",
                      G_CALLBACK (clone_repository_cb),
                      NULL);
}

GtkWidget *guit_toolbar_new (void)
{
    return GTK_WIDGET (g_object_new (GUIT_TOOLBAR_TYPE, NULL));
}

/* Callbacks */
void clone_repository_cb (GtkWidget *widget, gpointer data)
{
    /* Just a call to clone_dialog */
    guit_clone_dialog_new ();
}

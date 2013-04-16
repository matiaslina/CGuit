#include <gtk/gtk.h>
#include <glib.h>

#define GUIT_TOOLBAR_TYPE guit_toolbar_get_type ()

#define GUIT_TOOLBAR(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), GUIT_TOOLBAR_TYPE, GuitToolbar))
#define GUIT_TOOLBAR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST(klass, GUIT_TOOLBAR_TYPE, GuitToolbarClass))
#define GUIT_IS_TOOLBAR(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE(obj, GUIT_TOOLBAR_TYPE))
#define GUIT_IS_TOOLBAR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE(klass, GUIT_TOOLBAR_TYPE))
#define GUIT_TOOLBAR_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS(obj, GUIT_TOOLBAR_TYPE, GuitToolbarClass))
    

typedef struct {
    GtkToolbarClass parent_class;
} GuitToolbarClass;

typedef struct {
    GtkToolbar toolbar;
    
    GtkToolItem *clone;
} GuitToolbar;

GType guit_toolbar_get_type (void);

GtkWidget *guit_toolbar_new (void);

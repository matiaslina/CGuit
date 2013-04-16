#ifndef _GUIT_CLONE_INIT_DIALOG_H_
#define _GUIT_CLONE_INIT_DIALOG_H_

#include <gtk/gtk.h>

#define GUIT_CLONE_INIT_DIALOG_TYPE guit_clone_init_dialog_get_type ()

#define GUIT_CLONE_INIT_DIALOG(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), GUIT_CLONE_INIT_DIALOG_TYPE, GuitCloneInitDialog))
#define GUIT_CLONE_INIT_DIALOG_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST(klass, GUIT_CLONE_INIT_DIALOG_TYPE, GuitToolbarClass))
#define GUIT_IS_CLONE_INIT_DIALOG(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE(obj, GUIT_CLONE_INIT_DIALOG_TYPE))
#define GUIT_IS_CLONE_INIT_DIALOG_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE(klass, GUIT_CLONE_INIT_DIALOG_TYPE))
#define GUIT_CLONE_INIT_DIALOG_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS(obj, GUIT_CLONE_INIT_DIALOG_TYPE, GuitCloneInitDialogClass))
    
typedef struct {
    GtkDialogClass parent_class;
} GuitCloneInitDialogClass;

typedef struct {
    GtkDialog dialog;
} GuitCloneInitDialog;

GType guit_clone_init_dialog_get_type (void);

GtkWidget *guit_clone_init_dialog_new (void);

void guit_clone_dialog_new (void);

#endif

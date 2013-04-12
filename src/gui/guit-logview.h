#ifndef _GUIT_LOGVIEW_H_
#define _GUIT_LOGVIEW_H_

#include <gtk/gtk.h>

typedef struct _GuitLogView      GuitLogView;
typedef struct _GuitLogViewClass GuitLogViewClass;

#define GUIT_LOG_VIEW_TYPE guit_log_view_get_type ()

#define GUIT_LOG_VIEW(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), GUIT_LOG_VIEW_TYPE, GuitLogView))
#define GUIT_LOG_VIEW_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST(klass, GUIT_LOG_VIEW_TYPE, GuitLogViewClass))
#define GUIT_IS_LOG_VIEW(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE(obj, GUIT_LOG_VIEW_TYPE))
#define GUIT_IS_LOG_VIEW_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE(klass, GUIT_LOG_VIEW_TYPE))
#define GUIT_LOG_VIEW_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS(obj, GUIT_LOG_VIEW_TYPE, GuitLogViewClass))

struct _GuitLogViewClass
{
    GtkTextViewClass parent_class;
};

struct _GuitLogView
{
    GtkTextView view;
};

guint guit_log_view_get_type (void);

GtkWidget *guit_log_view_new (void);

void guit_log_view_update_last_line (GuitLogView *logview,gchar *new_line);

void guit_log_view_write_line (GuitLogView *logview,gchar *line);

void guit_log_view_clear (GuitLogView *logview);

#endif

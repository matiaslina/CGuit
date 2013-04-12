#ifndef _GUIT_LOG_TEXTVIEW_H_
#define _GUIT_LOG_TEXTVIEW_H_

#include <gtk/gtk.h>

GtkWidget *guit_log_textview_init (void);

void guit_log_textview_update_last_line (gchar *new_line);

void guit_log_textview_write_line (GtkTextView *view,gchar *line);

void guit_log_textview_clear (void);

#endif

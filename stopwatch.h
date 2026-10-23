#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <gtk/gtk.h>

void
start_stopwatch (GtkWidget *widget);

void
pause_stopwatch (GtkWidget *widget);

void
reset_stopwatch (GtkWidget *widget);

void
format_elapsed (gint64 us, gchar *buf, gsize len);

gboolean
update_stopwatch (GtkWidget     *label,
                  GdkFrameClock *clock,
                  gpointer       data);

#endif

#include "stopwatch.h"

/* 시간을 직접 세지 않고 단조 시계의 차이로 계산한다: 콜백이 늦게 불려도 오차가 쌓이지 않는다 */
static gint64 elapsed_us;   /* 일시정지 전까지 누적된 시간(µs) */
static gint64 started_at;   /* 달리는 중이면 시작 시각, 아니면 0 */

void
start_stopwatch (GtkWidget *widget)
{
  if (!started_at)
    started_at = g_get_monotonic_time ();
}

void
pause_stopwatch (GtkWidget *widget)
{
  if (started_at) {
    elapsed_us += g_get_monotonic_time () - started_at;
    started_at = 0;
  }
}

void
reset_stopwatch (GtkWidget *widget)
{
  elapsed_us = 0;
  started_at = 0;
}

/* HH:MM:SS.cc, 100시간이 되면 0으로 돌아간다 */
void
format_elapsed (gint64 us, gchar *buf, gsize len)
{
  gint64 cs = us / 10000;

  g_snprintf (buf, len, "%02u:%02u:%02u.%02u",
              (guint) (cs / 360000 % 100), (guint) (cs / 6000 % 60),
              (guint) (cs / 100 % 60), (guint) (cs % 100));
}

gboolean
update_stopwatch (GtkWidget     *label,
                  GdkFrameClock *clock,
                  gpointer       data)
{
  gchar buf[12];

  format_elapsed (elapsed_us + (started_at ? g_get_monotonic_time () - started_at : 0),
                  buf, sizeof buf);
  gtk_label_set_text (GTK_LABEL (label), buf);

  return G_SOURCE_CONTINUE;
}

#include "stopwatch.h"

static void
check (gint64 us, const gchar *expected)
{
  gchar buf[12];

  format_elapsed (us, buf, sizeof buf);
  g_assert_cmpstr (buf, ==, expected);
}

int
main (void)
{
  check (0, "00:00:00.00");
  check (9999, "00:00:00.00");                                  /* 1/100초 미만은 버린다 */
  check (1234567, "00:00:01.23");
  check (G_GINT64_CONSTANT (3723450000), "01:02:03.45");        /* 1시간 2분 3.45초 */
  check (G_GINT64_CONSTANT (359999990000), "99:59:59.99");
  check (G_GINT64_CONSTANT (360000000000), "00:00:00.00");      /* 100시간에서 0으로 */

  g_print ("format_elapsed: ok\n");
  return 0;
}

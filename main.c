#include "stopwatch.h"

static void
quit_cb (GtkWindow *window)
{
  gtk_window_close (window);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  /* 두 번째 실행은 이미 떠 있는 프로세스의 activate로 들어온다: 새 창 대신 기존 창을 올린다 */
  GtkWindow *existing = gtk_application_get_active_window (app);
  if (existing) {
    gtk_window_present (existing);
    return;
  }

  GtkBuilder *builder = gtk_builder_new_from_resource ("/org/xisik/gtkstopwatch/builder.ui");

  GObject *window = gtk_builder_get_object (builder, "window");
  gtk_window_set_application (GTK_WINDOW (window), app);

  /* 틱 콜백은 화면 프레임마다 불리고, 라벨이 사라지면 GTK가 알아서 제거한다 */
  GObject *label = gtk_builder_get_object (builder, "stopwatch");
  gtk_widget_add_tick_callback (GTK_WIDGET (label), update_stopwatch, NULL, NULL);

  GObject *button = gtk_builder_get_object (builder, "start");
  g_signal_connect (button, "clicked", G_CALLBACK (start_stopwatch), NULL);

  button = gtk_builder_get_object (builder, "pause");
  g_signal_connect (button, "clicked", G_CALLBACK (pause_stopwatch), NULL);

  button = gtk_builder_get_object (builder, "reset");
  g_signal_connect (button, "clicked", G_CALLBACK (reset_stopwatch), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (quit_cb), window);

  gtk_widget_set_visible (GTK_WIDGET (window), TRUE);

  g_object_unref (builder);
}

int
main (int   argc,
      char *argv[])
{
  GtkApplication *app = gtk_application_new ("org.xisik.gtkstopwatch", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

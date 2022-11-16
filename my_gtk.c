#include <gtk/gtk.h>

static void btn_clicked(GtkWidget *widget, gpointer data)
{
        g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(data)));
        gtk_editable_select_region(GTK_EDITABLE(data), 0,-1);
        gtk_editable_copy_clipboard(GTK_EDITABLE(data));
}

int main(int argc, char *argv[])
{
    GtkWidget *window, *grid;
    GtkWidget *label, *label_fn;
    GtkWidget *fn_entry;
    GtkWidget *button;

            //---------- CSS -------------
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    //---------------------------

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "MyApp");
    gtk_window_set_default_size(GTK_WINDOW(window), 370, 155);
    gtk_window_set_resizable (GTK_WINDOW(window), TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /*     Create a Grid     */
    grid = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER (grid), 15);
    gtk_widget_set_name(grid, "myGrid");
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(window), grid);

    /*     Create first Label     */
    label = gtk_label_new("Please enter your Information:");
    gtk_widget_set_margin_top(label, 25);
    gtk_widget_set_margin_start(label, 85);

    /*     Create second Label     */
    label_fn = gtk_label_new("First Name: ");
    gtk_widget_set_margin_start(label_fn, 10);

    /*     Create an Entry:     */
    fn_entry = gtk_entry_new();

    /*     Create a Button    */
    button = gtk_button_new_with_mnemonic("_Write text");
    g_signal_connect(button, "clicked", G_CALLBACK(btn_clicked), fn_entry);
    g_signal_connect(fn_entry, "activate", G_CALLBACK(btn_clicked), fn_entry);


    /*     Putting all together      */
    gtk_grid_attach(GTK_GRID(grid), label,      0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), label_fn,   0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), fn_entry,   1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button,     1, 2, 1, 1);

        // ---------------------------------------------------- CSS -----------------------------------------------------------
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
    // --------------------------------------------------------------------------------------------------------------------

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
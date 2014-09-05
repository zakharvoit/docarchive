#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <gtk/gtk.h>

#include "directory_view.h"
#include "directory_selection.h"
#include "browser.h"
#include "config.c"

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

Browser browser;

static void
tree_selection_changed_cb(GtkTreeSelection* selection,
                          gpointer UNUSED(data))
{
    char* path;
    char* buffer;
    struct stat st;

    path = get_selected_path(selection);
    buffer = strdup(path);
    strcpy(path, "file://");
    strcat(path, config.directory);
    strcat(path, "/");
    strcat(path, buffer);

    fflush(stdout);

    stat(path + 7, &st);
    if (S_ISREG(st.st_mode)) webkit_web_view_load_uri(browser.view, path);

    free(path);
    free(buffer);
}

static gboolean
delete_event_cb(GtkWidget* UNUSED(widget),
                GdkEvent* UNUSED(event),
                gpointer UNUSED(data))
{
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* paned;
    GtkWidget* tree;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    paned = gtk_hpaned_new();
    tree = get_directory_view(config.directory);
    browser = create_browser();

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event_cb), NULL);
    add_selection_callback(GTK_TREE_VIEW(tree), G_CALLBACK(tree_selection_changed_cb));

    gtk_container_add(GTK_CONTAINER(window), paned);
    gtk_paned_add1(GTK_PANED(paned), tree);
    gtk_paned_add2(GTK_PANED(paned), browser.container);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

#ifndef DIRECTORY_SELECTION_H
#define DIRECTORY_SELECTION_H

#include <gtk/gtk.h>

void add_selection_callback(GtkTreeView* view, GCallback callback);
char* get_selected_path(GtkTreeSelection* selection);

#endif // DIRECTORY_SELECTION_H

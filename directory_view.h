#ifndef DIRECTORY_VIEW_H
#define DIRECTORY_VIEW_H

#include <gtk/gtk.h>

enum
    {
        NAME_COLUMN,
        N_COLUMNS
    };

GtkWidget* get_directory_view(char* path);
GtkWidget* create_view_from_tree(GtkTreeStore* store);
void populate_store(char* base_path, GtkTreeStore* store, GtkTreeIter* parent, DIR* dir);

#endif // DIRECTORY_VIEW_H

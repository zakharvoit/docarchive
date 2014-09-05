#include <stdlib.h>
#include <string.h>

#include "directory_view.h"

GtkWidget* get_directory_view(char* path)
{
    GtkWidget* view;
    GtkTreeStore* store;
    DIR* dir;

    store = gtk_tree_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);

    populate_store(path, store, NULL, dir = opendir(path));
    closedir(dir);

    view = create_view_from_tree(store);
    g_object_unref(G_OBJECT(store));

    return view;
}

GtkWidget* create_view_from_tree(GtkTreeStore* store)
{
    GtkWidget* view;
    GtkTreeViewColumn* column;
    GtkCellRenderer *renderer;

    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(NULL, renderer,
                                                      "text", NAME_COLUMN,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    return view;
}

void populate_store(char* base_path, GtkTreeStore* store, GtkTreeIter* parent, DIR* dir)
{
    GtkTreeIter it;
    struct dirent *d;
    char *path;

    while ((d = readdir(dir))) {
        if (strcmp(d->d_name, "..") == 0
            || strcmp(d->d_name, ".") == 0) continue;

        gtk_tree_store_append(store, &it, parent);
        gtk_tree_store_set(store, &it,
                           NAME_COLUMN, d->d_name,
                           -1);

        if (d->d_type == DT_DIR) {
            path = malloc(sizeof(char) * (strlen(base_path) + strlen(d->d_name) + 2));
            strcpy(path, base_path);
            strcat(path, "/");
            strcat(path, d->d_name);

            populate_store(path, store, &it, opendir(path));

            free(path);
        }
    }
}

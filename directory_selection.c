#include "directory_selection.h"
#include "directory_view.h"

#include <stdlib.h>
#include <string.h>

void add_selection_callback(GtkTreeView* view, GCallback callback)
{
    GtkTreeSelection* select;

    select = gtk_tree_view_get_selection(view);
    gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
    g_signal_connect(G_OBJECT(select), "changed",
                     callback,
                     NULL);
}

char* get_selected_path(GtkTreeSelection* selection)
{
    GtkTreeIter iter;
    GtkTreePath* path;
    GtkTreeModel* model;
    char* tree[256]; // Max depth of directory tree
    int depth, i;
    char* full_path;

    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return NULL;

    depth = 0;
    path = gtk_tree_model_get_path(model, &iter);
    do {
        gtk_tree_model_get_iter(model, &iter, path);
        gtk_tree_model_get(model, &iter,
                           NAME_COLUMN, &tree[depth],
                           -1);
        ++depth;
    } while (gtk_tree_path_up(path)
             && gtk_tree_path_get_depth(path) > 0);

    full_path = (char*)malloc(sizeof(char) * 2048);
    *full_path = 0;
    for (i = depth - 1; i >= 0; --i) {
        if (i < depth - 1) strcat(full_path, "/");
        strcat(full_path, tree[i]);
        free(tree[i]);
    }

    gtk_tree_path_free(path);

    return full_path;
}

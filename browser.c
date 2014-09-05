#include "browser.h"

Browser create_browser()
{
    GtkWidget* scrolled_window;
    WebKitWebView* web_view;
    Browser b;

    web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(web_view));

    b.view = web_view;
    b.container = scrolled_window;

    return b;
}

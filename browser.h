#ifndef BROWSER_H
#define BROWSER_H

#include <webkit/webkit.h>

typedef struct
{
    WebKitWebView* view;
    GtkWidget* container;
} Browser;

Browser create_browser();

#endif // BROWSER_H


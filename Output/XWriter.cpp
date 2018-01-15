//
// Created by paul on 15.01.18.
//

#include "XWriter.hpp"

#include <unistd.h>		/* sleep(), etc.  */
#include <X11/Xlib.h>

XWriter::XWriter(int32_t width, int32_t height) : ImageWriter(width, height) {
    char *display_name = getenv("DISPLAY");  /* address of the X display.      */
    /*  in our window.			     */

    /* open connection with the X server. */
    display = XOpenDisplay(display_name);
    if (display == nullptr) {
        fprintf(stderr, "Cannot connect to X server '%s'\n",
              display_name);
        exit(1);
    }

    /* get the geometry of the default screen for our display. */
    screen_num = DefaultScreen(display);

    /* make the new window occupy 1/9 of the screen's size. */

    int win_border_width = 2;

    /* create a simple window, as a direct child of the screen's */
    /* root window. Use the screen's black and white colors as   */
    /* the foreground and background colors of the window,       */
    /* respectively. Place the new window's top-left corner at   */
    /* the given 'x,y' coordinates.                              */
    win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                              0, 0, width, height, win_border_width,
                              BlackPixel(display, screen_num),
                              BlackPixel(display, screen_num));

    /* make the window actually appear on the screen. */
    XMapWindow(display, win);

    /* flush all pending requests to the X server. */
    XFlush(display);

    unsigned long valuemask = 0;		/* which values in 'values' to  */
    /* check when creating the GC.  */
    XGCValues values;			/* initial values for the GC.   */

    gc = XCreateGC(display, win, valuemask, &values);
    if (gc < 0) {
        fprintf(stderr, "XCreateGC: \n");
    }
    XSync(display, false);

    XSetForeground(display, gc, WhitePixel(display, screen_num));
    XFlush(display);
}

void XWriter::set(uint32_t x, uint32_t y, ColorChannel channel, uint8_t val) {
    XDrawPoint(display, win, gc, x, y);
}

void XWriter::clear() {
    XClearWindow(display, win);
    XFlush(display);

    XWindowAttributes wndAttr;
    XGetWindowAttributes(display,win,&wndAttr);
    this->width = wndAttr.width;
    this->height = wndAttr.height;
}

void XWriter::write() {
    XFlush(display);
}

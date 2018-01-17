//
// Created by paul on 15.01.18.
//

#include "XWriter.hpp"

XWriter::XWriter(uint32_t width, uint32_t height) : ImageWriter(width, height) {
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
    XGCValues values{};			/* initial values for the GC.   */

    gc = XCreateGC(display, win, valuemask, &values);
    if (gc < 0) {
        fprintf(stderr, "XCreateGC: \n");
    }
    XSync(display, false);

    XSetForeground(display, gc, WhitePixel(display, screen_num));
    XFlush(display);
}

void XWriter::set(uint32_t x, uint32_t y, uint8_t r, uint8_t b, uint8_t g) {
 /* first, find the default visual for our screen. */
    static Visual* default_visual = DefaultVisual(display, DefaultScreen(display));
/* this creates a new color map. the number of color entries in this map */
/* is determined by the number of colors supported on the given screen.  */
    static Colormap my_colormap = XCreateColormap(display,
                                           win,
                                           default_visual,
                                           AllocNone);
    XColor xcolour{};
// I guess XParseColor will work here
    xcolour.red = (uint16_t)(r*256);
    xcolour.green = (uint16_t)(g*256);
    xcolour.blue = (uint16_t)(b*256);
    XAllocColor(display, my_colormap, &xcolour);

    XSetForeground(display, gc, xcolour.pixel);
    XDrawPoint(display, win, gc, x, height-y);
}

void XWriter::clear() {
    XClearWindow(display, win);
    XFlush(display);

    XWindowAttributes wndAttr{};
    XGetWindowAttributes(display,win,&wndAttr);
    this->width = (unsigned int)wndAttr.width;
    this->height = (unsigned int)wndAttr.height;
}

void XWriter::write() {
    XFlush(display);
}

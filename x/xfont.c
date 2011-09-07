/*
  $ cc -o xfont xfont.c -Wall -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
  $ ./xfont
  http://www.ainet.or.jp/~inoue/font/
 */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define F_SIZE                  14
#define COL                     30
#define ROW                     10

#define W_WIDTH                 (F_SIZE * COL)
#define W_HEIGHT                (F_SIZE * ROW)

int
main(int argc, char *argv[])
{
    Display        *display;
    int             screen;
    GC              gc;
    Window          window;
    XWMHints        hints;
    Atom            protocols;
    XEvent          event;
    unsigned long   mask;
    Font            xfont1, xfont2;

    display = XOpenDisplay("");
    screen = DefaultScreen(display);
    gc = DefaultGC(display, screen);

    /*
     * Font names are hard-coded.
     */
    xfont1 = XLoadFont(display, "a14");
    xfont2 = XLoadFont(display, "k14");

    window = XCreateSimpleWindow(display, RootWindow(display, screen),
     0, 0, W_WIDTH, W_HEIGHT, 2,
     BlackPixel(display, screen), WhitePixel(display, screen));
    XStoreName(display, window, "XFontStruct demo");

    hints.flags = InputHint;
    hints.input = True;
    XSetWMHints(display, window, &hints);
    protocols = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, window, &protocols, 1);

    mask = ExposureMask;
    XSelectInput(display, window, mask);

    XMapWindow(display, window);

    for (;;) {
        XNextEvent(display, &event);
        if (XFilterEvent(&event, window) == True)
            continue;
        switch (event.type) {
            case Expose: {
                XSetFont(display, gc, xfont1);
                XDrawString(display, window, gc, 10, 50, "abcdef", 6);
                XSetFont(display, gc, xfont2);
                /* JIS */
                XDrawString16(display, window, gc, 10, 80,
                 (XChar2b *) "\x24\x22\x24\x24", 4);
                break;
            }
            default: {
                break;
            }
        }
    }
}

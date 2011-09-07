#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

int
main (
  int argc,
  char * * argv ) {
  Display * pdisplay = NULL;
  Window window = 0;
    do {
      GC gc;
      unsigned long iBgColor;
      unsigned long iFgColor;
        pdisplay = XOpenDisplay(NULL);
        iBgColor = WhitePixel(pdisplay, 0);
        iFgColor = BlackPixel(pdisplay, 0);
        if (1) {
            window = DefaultRootWindow(pdisplay);
        } else {
            window = XCreateSimpleWindow(pdisplay,
             DefaultRootWindow(pdisplay),
             0, 0, 200, 100,
             0, 0, iBgColor );
        }
        XSetStandardProperties(pdisplay, window, "Hello Title", "IconName",
         None, argv, argc, NULL );
        gc = XCreateGC(pdisplay, window, 0, 0);
        XSetBackground(pdisplay, gc, iBgColor);
        XSetForeground(pdisplay, gc, iFgColor);
        XSelectInput(pdisplay, window, ExposureMask);
        XMapRaised(pdisplay, window);
        while (1) {
          XEvent xevent;
            XNextEvent(pdisplay, & xevent);
            switch (xevent.type) {
                case Expose: {
                  const char * pszMessage = "Hello World!";
                    XDrawImageString(pdisplay, window, gc, 8, 16, pszMessage,
                     strlen(pszMessage) );
                    break;
                }
                default: {
                    break;
                }
            }
        }
    } while (0);
    if (pdisplay) {
        if (window) { XDestroyWindow(pdisplay, window); }
        XCloseDisplay(pdisplay);
    }
    return (0);
}

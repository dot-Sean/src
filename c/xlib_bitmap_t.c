#include <stdio.h>
/* to refer members */
//#define XLIB_ILLEGAL_ACCESS
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
/* sleep() */
#include <unistd.h>
/* strlen() */
#include <string.h>
/* KeySym */
#include <X11/keysym.h>
/* signal() */
#include <signal.h>
/* exit() */
#include <stdlib.h>
/* waitpid() */
#include <sys/wait.h>
/* pthread_*() */
#include <pthread.h>

#include "test.xpm"

static unsigned long
getColor (
  Display * pdisplay,
  const char * pszColor ) {
  Colormap colormap;
  XColor xcolorScreen, xcolorExact;
    colormap = DefaultColormap(pdisplay, 0);
    XAllocNamedColor(pdisplay, colormap, pszColor,
     & xcolorScreen, & xcolorExact );
    return (xcolorScreen.pixel);
}

static struct ParentInfo {
    Display * pdisplay;
    Window hwindow;
    int rc;
    int fGotChildStat;
} * pparentinfo_ = NULL;

void
sendEvent (
  Display * pdisplay,
  Window hwindow,
  const char * pszId ) {
  Display * pdisplayTmp = NULL;
  XClientMessageEvent xmsgevent;
    if (! pdisplay) {
        pdisplay = pdisplayTmp = XOpenDisplay(NULL);
    }
    xmsgevent.type = ClientMessage;
    xmsgevent.display = pdisplay;
    xmsgevent.window = pparentinfo_->hwindow;
    xmsgevent.message_type = XInternAtom(xmsgevent.display,
     pszId, False );
    xmsgevent.format = 32;
    XLockDisplay(pdisplay);
    XSendEvent(xmsgevent.display, xmsgevent.window,
     0, NoEventMask, (XEvent *) & xmsgevent );
    XUnlockDisplay(pdisplay);
    if (pdisplayTmp) {
        XCloseDisplay(pdisplayTmp);
    }
}

static void *
doChild (
  void * pv ) {
  int i;
    for (i = 0; i < 5; i++) {
        while (! pparentinfo_) {
            usleep(1000);
        }
        sendEvent(NULL, pparentinfo_->hwindow, "Hello");
        sleep(1);
    }
    return (NULL);
}

static void *
doTimer (
  void * pv ) {
    while (! pparentinfo_) {
        usleep(1000);
    }
    while (1) {
        usleep(2000);
        sendEvent(NULL, pparentinfo_->hwindow, "Timer");
    }
    return (NULL);
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  Display * pdisplay = NULL;
  /* "Window" is XID ID (unsigned long) */
  Window hwindow = 0;
  Window hwindowButton = 0;
  GC hgc = 0;
  struct ParentInfo parentinfo;
    parentinfo.fGotChildStat = 0;
    do {
      Pixmap pixmap0;
      Pixmap pixmap1;
      XpmAttributes xpmattrs0;
      XpmAttributes xpmattrs1;
      XEvent xevent;
      int fLoop = 1;
      XWindowAttributes xattrs;
      pthread_t pthreadChild;
      pthread_t pthreadTimer;
      Atom atomHello;
      Atom atomTimer;
      Atom atomClose;
      static int x = 0;
        XInitThreads();
        pthread_create(& pthreadChild, (void *) 0, doChild, NULL);
        pthread_create(& pthreadTimer, (void *) 0, doTimer, NULL);
        if (! (pdisplay = XOpenDisplay(NULL))) {
            break;
        }
        parentinfo.pdisplay = pdisplay;
        //fprintf(stderr, "d: %s\n", pdisplay->display_name);
        fprintf(stderr, "d: %s\n", DisplayString(pdisplay));
        if (! (hwindow = XCreateSimpleWindow(
         pdisplay, // display
         DefaultRootWindow(pdisplay), // parent
         0, // x
         0, // y
         100, // width
         100, // height
         0, // border_witdh
         getColor(pdisplay, "black"), // border
         getColor(pdisplay, "white") ))) { // background
            break;
        }
        parentinfo.hwindow = hwindow;
        XSelectInput(pdisplay, hwindow, ExposureMask | KeyPressMask);
        /* todo: magic number */
        if (! (hwindowButton = XCreateSimpleWindow(pdisplay, hwindow,
         10, 10, 60, 30, 3, getColor(pdisplay, "black"),
         getColor(pdisplay, "white" )))) {
            break;
        }
        XSelectInput(pdisplay, hwindowButton, ButtonPressMask | \
         ButtonReleaseMask | ExposureMask );
        if (! (hgc = XCreateGC(pdisplay, hwindow, 0, 0))) {
            break;
        }
        xpmattrs0.alloc_close_colors = True;
        xpmattrs0.closeness = 65535;
        xpmattrs0.valuemask = XpmAllocCloseColors | XpmCloseness;
        if (XpmCreatePixmapFromData(pdisplay, hwindow,
         test_xpm, & pixmap0, NULL, & xpmattrs0 ) != 0) {
            break;
        }
        /* http://www.fenix.ne.jp/~cdrtk/misc/xpm/advanced.html */
        fprintf(stderr, "xpmattrs0 - width: %d, height: %d\n",
         xpmattrs0.width, xpmattrs0.height );
        xpmattrs1.alloc_close_colors = True;
        xpmattrs1.closeness = 65535;
        xpmattrs1.valuemask = XpmAllocCloseColors | XpmCloseness;
        if ((XpmReadFileToPixmap(pdisplay, hwindow,
         "yahoo_logo.xpm", & pixmap1, NULL, & xpmattrs1 )) != 0) {
            break;
        }
        XMapWindow(pdisplay, hwindow);
        XMapSubwindows(pdisplay, hwindow);
        XResizeWindow(pdisplay, hwindow,
         (xpmattrs0.width > xpmattrs1.width)? xpmattrs0.width: xpmattrs1.width,
         xpmattrs0.height + xpmattrs1.height );
        /* Window attributes are reflected after calling XFlush() */
        XFlush(pdisplay);
        XGetWindowAttributes(pdisplay, hwindow, & xattrs);
        fprintf(stderr, "xattrs - x: %d, y: %d, width: %d, height: %d\n",
         xattrs.x,
         xattrs.y,
         xattrs.width,
         xattrs.height );
        fprintf(stderr, "I'm your father\n");
        pparentinfo_ = & parentinfo;
        atomHello = XInternAtom(pdisplay, "Hello", False);
        atomTimer = XInternAtom(pdisplay, "Timer", False);
        atomClose = XInternAtom(pdisplay, "WM_DELETE_WINDOW", False);
        while (fLoop) {
            XNextEvent(pdisplay, & xevent);
            switch (xevent.type) {
                /* todo: cliping */
                /* http://homepage3.nifty.com/rio_i/lab/xlib/007expose.htm */
                case (Expose): {
                    /* Number of proceeding expose event. 0 means the last */
                    if (xevent.xexpose.count == 0) {
                      XWindowAttributes xattrs;
                      const char szButton[] = "BUTTON";
                        XGetWindowAttributes(pdisplay, hwindowButton,
                         & xattrs );
                        /* todo: magic number */
                        XDrawString(pdisplay, hwindowButton, hgc,
                         10, xattrs.height / 2, szButton, strlen(szButton) );
                        XCopyArea(pdisplay, pixmap0, hwindow, hgc,
                         0, // x
                         0, // y
                         xpmattrs0.width, // width
                         xpmattrs0.height, // height
                         0, // dest x
                         0 ); // dest y
                        XCopyArea(pdisplay, pixmap1, hwindow, hgc,
                         0, 0, xpmattrs1.width, xpmattrs1.height,
                         0, xpmattrs0.height );
                    }
                    break;
                }
                case (MappingNotify): {
                    //XRefreshKeyboardMapping(& xevent);
                    break;
                }
                case (KeyPress): {
                  char sz[256];
                  KeySym keysym;
                  XComposeStatus xcomposestat;
                  int n;
                    n = XLookupString(& xevent.xkey, sz, sizeof (sz), 
                     & keysym, & xcomposestat );
                    if (n > 0) {
                        sz[n] = '\0';
                        fprintf(stderr, "d: %d, %s\n", (int) keysym, sz);
                        if (keysym == XK_space) {
                            fLoop = 0;
                        }
                    }
                    break;
                }
                case (ButtonRelease): {
                  XWindowAttributes xattrs;
                  XGetWindowAttributes(pdisplay, hwindowButton, & xattrs);
                    if (
                     xevent.xbutton.window == hwindowButton &&
                     xattrs.x < xevent.xbutton.x &&
                     xattrs.y < xevent.xbutton.y &&
                     xevent.xbutton.x < xattrs.x + xattrs.width &&
                     xevent.xbutton.y < xattrs.y + xattrs.height ) {
                        fLoop = 0;
                    }
                    break;
                }
                case (ClientMessage): {
                    if        (xevent.xclient.message_type == atomHello) {
                        fprintf(stderr, "Got 0\n");
                    } else if (xevent.xclient.message_type == atomTimer) {

                        XCopyArea(pdisplay, pixmap0, hwindow, hgc,
                         0, // x
                         0, // y
                         xpmattrs0.width, // width
                         xpmattrs0.height, // height
                         x, // dest x
                         0 ); // dest y
                        x -= 1;
                        if (x < -300 ) {
                            x = 1000;
                        }
                        //fprintf(stderr, "1");
                    } else if (xevent.xclient.message_type == atomClose) {
                        fprintf(stderr, "XXXXX\n");
                        fLoop = 0;
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
        if (parentinfo.fGotChildStat) {
            rc = WEXITSTATUS(parentinfo.rc);
        } else {
            rc = 0;
        }
    } while (0);
    if (hgc) { XFreeGC(pdisplay, hgc); }
    if (hwindowButton) { XDestroyWindow(pdisplay, hwindowButton); }
    if (hwindow) { XDestroyWindow(pdisplay, hwindow); }
    if (pdisplay) { XCloseDisplay(pdisplay); }
    return (rc);
}

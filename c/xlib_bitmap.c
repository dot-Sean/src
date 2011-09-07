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
    int iPid;
    Window hwindow;
    int rc;
    int fGotChildStat;
} * pparentinfo_ = NULL;

void
handler (
  int i ) {
  int rc;
    fprintf(stderr, "Caught - i: %d\n", i);
    if (
     pparentinfo_ &&
     pparentinfo_->iPid > 0 &&
     waitpid(pparentinfo_->iPid, & rc, WNOHANG) == pparentinfo_->iPid ) {
      Display * pdisplay = NULL;
        do {
          XClientMessageEvent xmsgevent;
            pparentinfo_->iPid = 0;
            /* Don't use the display which has been opended by the */
            /* main thread */
            if (! (pdisplay = XOpenDisplay(NULL))) {
                break;
            }
            fprintf(stderr, "Ret: %d, %d\n", rc, WEXITSTATUS(rc));
            if (WIFEXITED(rc)) {
                fprintf(stderr, "EXITED\n");
            }
            pparentinfo_->fGotChildStat = 1;
            pparentinfo_->rc = rc;
            xmsgevent.type = ClientMessage;
            xmsgevent.display = pdisplay;
            xmsgevent.window = pparentinfo_->hwindow;
            xmsgevent.message_type = XInternAtom(xmsgevent.display,
             "Hello", False );
            xmsgevent.format = 32;
            XSendEvent(xmsgevent.display, xmsgevent.window,
             0, NoEventMask, (XEvent *) & xmsgevent );
            fprintf(stderr, "Sent\n");
#if 0
            //XPutBackEvent(xmsgevent.display, (XEvent *) & xmsgevent);
            //XSync(xmsgevent.display, 0);
            //XFlush(xmsgevent.display);
            //XWindowEvent(xmsgevent.display, xmsgevent.window,
            // NoEventMask, (XEvent *) & xmsgevent );
#endif
        } while (0);
        if (pdisplay) { XCloseDisplay(pdisplay); }
    }
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
    parentinfo.iPid = 0;
    parentinfo.fGotChildStat = 0;
    do {
      Pixmap pixmap0;
      Pixmap pixmap1;
      XpmAttributes xpmattrs0;
      XpmAttributes xpmattrs1;
      XEvent xevent;
      int fLoop = 1;
      XWindowAttributes xattrs;
        signal(SIGCHLD, handler);
        if ((parentinfo.iPid = fork()) == 0) {
          int i;
            for (i = 0; i < 5; i ++) {
                sleep(1);
                fprintf(stderr, "I'm the child - %d\n", i);
            }
            exit(1);
        }
        //kill(iPid, SIGINT);
        kill(parentinfo.iPid, SIGSTOP);
        if (! (pdisplay = XOpenDisplay(NULL))) {
            break;
        }
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
        kill(parentinfo.iPid, SIGCONT);
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
                  Atom atom = XInternAtom(pdisplay, "Hello", False);
                    if (xevent.xclient.message_type == atom) {
                        fprintf(stderr, "Got\n");
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
    if (parentinfo.iPid > 0) {
        /* Otherwise an event will be sent by the handler. */
        signal(SIGCHLD, SIG_IGN);
        kill(parentinfo.iPid, SIGKILL);
    }
    if (hgc) { XFreeGC(pdisplay, hgc); }
    if (hwindowButton) { XDestroyWindow(pdisplay, hwindowButton); }
    if (hwindow) { XDestroyWindow(pdisplay, hwindow); }
    if (pdisplay) { XCloseDisplay(pdisplay); }
    return (rc);
}

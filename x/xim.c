/*
 * Origianl is <a href=http://www.ainet.or.jp/~inoue/im/xim.html>here</a>.
 */

#include <stdio.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#define DefaultFontName       "-*-*-*-R-Normal--14-130-75-75-*-*"
#define F_SIZE                  14
#define NumCol                  30
#define NumRow                  10

#define W_WIDTH                 (F_SIZE * NumCol)
#define W_HEIGHT                (F_SIZE * (NumRow + 1))

int
main(
  int argc,
  char * * argv ) {
  Display * pdisplay;
  int iScreen;
  GC gc;
  Window window;
  XWMHints hints;
  Atom protocols;
  XFontSet xfontset;
  char * * ppszMissing;
  int nMissing;
  char * pszDef;
  XFontSetExtents * xfontsetextents;
  int dec;
  XIM xim;
  XIC xic;
  XRectangle s_rect;
  XPoint spot;
  XVaNestedList preedit_attr;
  XVaNestedList status_attr;
  XEvent event;
  unsigned long mask;
  unsigned long fevent;
  int len = 128;
  char string[128];
  char s_tab[NumRow][128];
  int i;
  int row = 0;
  int col = 0;
  KeySym keysym;
  int count = 0;
  Status status;
    pdisplay = XOpenDisplay("");
    iScreen = DefaultScreen(pdisplay);
    gc = DefaultGC(pdisplay, iScreen);
    if (setlocale(LC_CTYPE, "") == (void *) 0) {
        fprintf(stderr, "Error: setlocale()\n");
        exit(0);
    }
    xfontset = XCreateFontSet(
     pdisplay,
     DefaultFontName,
     & ppszMissing, /* missing_charset_list_return */
     & nMissing, /* missing_charset_count_return */
     & pszDef ); /* def_string_return */
    xfontsetextents = XExtentsOfFontSet(xfontset);
    dec = xfontsetextents->max_logical_extent.height -
     (- xfontsetextents->max_logical_extent.y);
    /* ------------------------------------------------------------ */
    /* Main window */
    window = XCreateSimpleWindow(pdisplay, RootWindow(pdisplay, iScreen),
     0, 0, W_WIDTH, W_HEIGHT, 2,
     BlackPixel(pdisplay, iScreen), WhitePixel(pdisplay, iScreen));
    XStoreName(pdisplay, window, "XIM demo - Over window");
    hints.flags = InputHint;
    hints.input = True;
    XSetWMHints(pdisplay, window, &hints);
    protocols = XInternAtom(pdisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(pdisplay, window, &protocols, 1);
    /* Open X Input Method. Connection to XIM server. */
    if ((xim = XOpenIM(pdisplay, (void *) 0, (void *) 0, (void *) 0)) ==
     (void *) 0 ) {
        fprintf(stderr, "Error: XOpenIM()\n");
        exit(0);
    }
    spot.x = F_SIZE / 2 * col;
    spot.y = F_SIZE * (row + 1);
    preedit_attr = XVaCreateNestedList((void *) 0,
     XNSpotLocation, &spot, XNFontSet, xfontset, (void *) 0);
    s_rect.x = F_SIZE * 0;
    s_rect.y = F_SIZE * NumRow;
    s_rect.width = W_WIDTH;
    s_rect.height = F_SIZE * 1;
    status_attr = XVaCreateNestedList((void *) 0,
     XNArea, &s_rect, XNFontSet, xfontset, (void *) 0);
    /* Create X Input Context for a window */
    xic = XCreateIC(xim, XNInputStyle, XIMPreeditPosition | XIMStatusArea,
     XNClientWindow, window, XNPreeditAttributes, preedit_attr,
     XNStatusAttributes, status_attr, (void *) 0 );
    if (xic == (void *) 0) {
        printf("Error : XCreateIC() !\n");
        XCloseIM(xim);
        exit(0);
    }
    XFree(preedit_attr);
    XFree(status_attr);
    XGetICValues(xic, XNFilterEvents, &fevent, (void *) 0);
    mask = ExposureMask | KeyPressMask | FocusChangeMask;
    XSelectInput(pdisplay, window, mask | fevent);
    /* ------------------------------------------------------------ */
    for (i = 0; i < NumRow; i++) {
        s_tab[i][0] = (void *) 0;
    }
    XMapWindow(pdisplay, window);
    for (;;) {
        XNextEvent(pdisplay, &event);
        if (XFilterEvent(&event, (void *) 0) == True)
            continue;
        switch (event.type) {
            case FocusIn: {
                XSetICFocus(xic);
                break;
            }
            case FocusOut: {
                XUnsetICFocus(xic);
                break;
            }
            case Expose: {
                for (i = 0; i < NumRow; i++)
                    XmbDrawString(pdisplay, window, xfontset, gc, 0,
                     F_SIZE * (i + 1), s_tab[i], strlen(s_tab[i]));
                break;
            }
            case KeyPress: {
                count = XmbLookupString(xic, (XKeyPressedEvent *) & event,
                 string, len, &keysym, &status);
                if (status == XLookupBoth && keysym == XK_Return) {
                    row = (++row) % NumRow;
                    col = 0;
                    s_tab[row][0] = (void *) 0;
                    XClearArea(pdisplay, window, 0, F_SIZE * row + dec,
                     W_WIDTH, F_SIZE, False);
                } else if (status == XLookupChars || status == XLookupBoth) {
                    XmbDrawString(pdisplay, window, xfontset, gc,
                     F_SIZE / 2 * col, F_SIZE * (row + 1), string, count);
                    for (i = 0; i < count; i++, col++)
                        s_tab[row][col] = string[i];
                    s_tab[row][col] = (void *) 0;
                }
                spot.x = F_SIZE / 2 * col;
                spot.y = F_SIZE * (row + 1);
                preedit_attr =
                 XVaCreateNestedList((void *) 0, XNSpotLocation, &spot,
                  (void *) 0 );
                XSetICValues(xic, XNPreeditAttributes, preedit_attr,
                 (void *) 0 );
                XFree(preedit_attr);
                break;
            }
            case ClientMessage: {
                if (event.xclient.data.l[0] == protocols) {
                    XDestroyIC(xic);
                    XCloseIM(xim);
                    XDestroyWindow(pdisplay, window);
                    XCloseDisplay(pdisplay);
                    exit(0);
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

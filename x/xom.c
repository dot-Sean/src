/*
  $ cc -o xom xom.c -Wall -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
  $ ./xom
  
  A sample program to output English and Japanese.
  Derived from a program that is formerly provided by Sun.
  See.
  http://www.ainet.or.jp/~inoue/font/
 */
#include <stdio.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#define DEFAULT_FONT_NAME       "-*-*-*-r-normal--*-130-75-75-*-*-*-*"
/* Use commma(,), when indicating character-sets.
#define DEFAULT_FONT_NAME       "-*-*-*-r-normal--*-130-75-75-*-*-iso8859-1,-misc-*-*-r-normal--*-130-75-75-*-*-jisx0208.1983-0,-misc-*-*-r-normal--*-130-75-75-*-*-jisx0201.1976-0"
*/
#define F_SIZE                  14
#define COL                     30
#define ROW                     10

#define W_WIDTH                 (F_SIZE * COL)
#define W_HEIGHT                (F_SIZE * (ROW+1))


int
main(int argc, char *argv[])
{
	Display *display;
	int screen;
	GC gc;
	Window window;
	XWMHints hints;
	Atom protocols;
	XOM om;
	XOC oc;
	XOMCharSetList cslist;
	XOMOrientation orientation;
	Bool direction;
	Bool contextdrawing;
	char **missing_list;
	int missing_count;
	char *def_string;
	XFontSetExtents *fs_ext;
	int dec;
	XIM im;
	XIC ic;
	XRectangle s_rect;
	XPoint spot;
	XVaNestedList preedit_attr, status_attr;
	XEvent event;
	unsigned long mask, fevent;
	int len = 128;
	char string[128], s_tab[ROW][128];
	int i, row = 0, col = 0;
	KeySym keysym;
	int count = 0;
	Status status;

	display = XOpenDisplay("");
	screen  = DefaultScreen(display);
	gc = DefaultGC(display,screen);
	
	if (setlocale(LC_CTYPE, "") == NULL) {
		fprintf(stderr, "Error : setlocale() !\n");
		exit(1);
	}

	om = XOpenOM(display, NULL, NULL, NULL);
	if (om) {
		printf("locale of XOM: %s\n", XLocaleOfOM(om));
		XGetOMValues(om,
					 XNRequiredCharSet, &cslist,
					 XNQueryOrientation, &orientation,
					 XNDirectionalDependentDrawing, &direction,
					 XNContextualDrawing, &contextdrawing,
					 NULL);
		/* We could create fontset list from these. */
		for (i = 0; i < cslist.charset_count; i++) {
			printf("needed charset[%d]: %s\n", i, cslist.charset_list[i]);
		}
	} else {
		printf("XOpenOM error\n");
		exit(1);
	}
	
	oc = XCreateOC(om,
				   XNBaseFontName, DEFAULT_FONT_NAME,
				   NULL);
	if (oc) {
		XGetOCValues(oc, 
					 XNMissingCharSet, &missing_count,
					 XNRequiredCharSet, &missing_list,
					 XNDefaultString, &def_string,
					 NULL);
		for (i = 0; i < missing_count; i++) {
			printf("missing_list[%d]: %s\n", i, missing_list[i]);
		}
	} else {
		printf("XCreateOC error\n");
		exit(1);
	}

	fs_ext = XExtentsOfFontSet(oc);
	dec = fs_ext->max_logical_extent.height-(-fs_ext->max_logical_extent.y);

	window = XCreateSimpleWindow(display, RootWindow(display, screen),
								 0, 0, W_WIDTH, W_HEIGHT, 2,
								 BlackPixel(display, screen),
								 WhitePixel(display, screen));
	XStoreName(display, window, "XOM demo - Over window");
	
	hints.flags = InputHint;
	hints.input = True;
	XSetWMHints(display, window, &hints);
	protocols = XInternAtom(display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(display, window, &protocols, 1);
	
	if ((im = XOpenIM(display, NULL, NULL, NULL)) == NULL) {
		printf("Error : XOpenIM() !\n");
		exit(0);
	}

	spot.x = F_SIZE/2 * col;
	spot.y = F_SIZE * (row+1);
	preedit_attr = XVaCreateNestedList(0,
									   XNSpotLocation, &spot,
									   XNFontSet, oc,
									   /*
									   XNForeground, WhitePixel(display, screen),
									   XNBackground, BlackPixel(display, screen),
									   */
									   NULL);
	s_rect.x = F_SIZE * 0;
	s_rect.y = F_SIZE * ROW;
	s_rect.width = W_WIDTH;
	s_rect.height = F_SIZE * 1;
	status_attr = XVaCreateNestedList(0,
									  XNArea, &s_rect,
									  XNFontSet, oc,
									  NULL);
	
	ic = XCreateIC(im,
				   XNInputStyle, XIMPreeditPosition | XIMStatusArea,
				   XNClientWindow, window,
				   XNPreeditAttributes, preedit_attr,
				   XNStatusAttributes, status_attr,
				   NULL);
	if (ic == NULL) {
		printf("Error : XCreateIC() !\n");
		XCloseIM(im);
		exit(1);
	}
	XFree(preedit_attr);
	XFree(status_attr);

	XGetICValues(ic, XNFilterEvents, &fevent, NULL);
	mask = ExposureMask | KeyPressMask | FocusChangeMask;
	XSelectInput(display, window, mask|fevent);
	
	for (i = 0; i < ROW; i++)
		s_tab[i][0] = '\0';

	XMapWindow(display, window);
	
	for (;;) {
		XNextEvent(display, &event);
		if (XFilterEvent(&event, window) == True)
			continue;
		switch (event.type){
		case FocusIn :
			XSetICFocus(ic);
			break;
		case FocusOut :
			XUnsetICFocus(ic);
			break;
		case Expose :
			for (i = 0; i < ROW; i++) {
				XmbDrawString(display, window, oc, gc, 0,
							  F_SIZE*(i+1),
							  s_tab[i], strlen(s_tab[i]));
			}
			break;
		case KeyPress :
			count = XmbLookupString(ic,(XKeyPressedEvent*)&event,
									string, len, &keysym, &status);
			if (status == XLookupBoth && keysym == XK_Return) {
				row = (++row)%ROW;
				col = 0;
				s_tab[row][0] = '\0';
				XClearArea(display, window, 0, F_SIZE*row+dec,
						   W_WIDTH, F_SIZE, False);
			}
			else if (status == XLookupChars || status == XLookupBoth) {
				XmbDrawString(display, window, oc, gc,
							  F_SIZE/2*col, F_SIZE*(row+1),
							  string, count);
				for (i = 0; i < count; i++, col++) {
					s_tab[row][col] = string[i];
				}
				s_tab[row][col] = '\0';
			}
			spot.x = F_SIZE/2 * col;
			spot.y = F_SIZE * (row+1);
			preedit_attr = XVaCreateNestedList(0,
											   XNSpotLocation, &spot,
											   NULL);
			XSetICValues(ic,XNPreeditAttributes,preedit_attr,NULL);
			XFree(preedit_attr);
			break;
		case ClientMessage :
			if (event.xclient.data.l[0] == protocols) {
				XDestroyOC(oc);
				XCloseOM(om);
				XDestroyIC(ic);
				XCloseIM(im);
				XDestroyWindow(display, window);
				XCloseDisplay(display);
				exit(0);
			}
			break;
		defaults:
			break;
		}
	}
}

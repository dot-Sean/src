PREFIX=/usr

CC=gcc
CFLAGS=-Wall -I/usr/X11R6/include
LDFLAGS=-L$(PREFIX)/X11R6/lib -lX11

all: xim

xim: xim.c
	$(CC) $(CFLAGS) $(LDFLAGS) -DNeedVarargsPrototypes -o $@ $<

xom: xom.c

xfont: xfont.c

clean:
	rm -fr xim xom xfont *~

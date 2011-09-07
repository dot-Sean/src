CFLAGS=-g3 -O0 -Wall $(shell pkg-config --cflags gobject-2.0)
LDFLAGS=$(shell pkg-config --libs gobject-2.0)

all: mygstring

mygstring: mygstring.o

clean:
	rm -f mygstring *~ *.o

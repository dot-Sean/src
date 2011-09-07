prefix=single_instance

CC=gcc
CFLAGS=$(shell pkg-config --cflags dbus-glib-1) -Wall -O0
LDFLAGS=$(shell pkg-config --libs dbus-glib-1)

singleinst: singleinst.o

singleinst.o: singleinst.c single-instance-glue.h
	$(CC) -c $(CFLAGS) -o $@ $<

single-instance-glue.h: single-instance.xml
	dbus-binding-tool --mode=glib-server --output=$@ \
	 --prefix=$(prefix) $^

clean:
	rm -f single-instance-glue.h *~ singleinst *.o

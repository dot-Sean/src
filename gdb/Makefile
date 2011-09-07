CFLAGS=-g -O0 -Wall
NLDFLAGS=

all: newt libtest

# ====================================================================

.PHONY: force

newt: newt.c
	gcc $(CFLAGS) -o $@ $^ $(NLDFLAGS) -lnewt

# --------------------------------------------------------------------

# Prepare output terminal for newt.
prep_output: dumb
	tty > newt_tty
	#while true; do sleep 1; done < /dev/null > /dev/null 2>&1
	./dumb

debug_newt: newt
	@ \
	if test -r newt_tty ; \
	then \
	  newt_tty=`cat newt_tty` ; \
	  gdb --command=$@.gdb --tty=$$newt_tty --quiet $< ; \
        else \
          echo Execute \"make prep_output\" on another terminal. ; \
	fi

# ====================================================================

.PHONY: libs

lib/libstest.a:
	make -C lib slib

LLDFLAGS=-Llib -ldtest

libtest: libtest.o lib/libstest.a
	make -C lib dlib
	gcc $(LLDFLAGS) -o $@ $^

libtest_test: libtest
	LD_LIBRARY_PATH=./lib/ gdb --args ./libtest hello

# ====================================================================

coredump: coredump.o

debug_core: coredump
	rm -f core
	-./coredump
	gdb coredump core

# ====================================================================

waitattach:

# ====================================================================

clean:
	rm -f settrace dumb newt newt_tty libtest *.o *~ core coredump
	make -C lib clean


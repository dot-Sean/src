CYGWIN=n

ifeq ($(CYGWIN),y)
PTHREAD_LIB=
else
PTHREAD_LIB = -lpthread
endif

all: str_test str_cpp_test str_ptr_test

clean-bin:
	for i in *; \
	do \
	  if file -i $$i 2> /dev/null | grep \
	   -e application/x-execut \
	   -e application/x-object \
	   > /dev/null 2>&1; \
	  then \
	    echo Removing executable \"$$i\".; \
	    rm -f $$i; \
	  fi \
	done

clean: clean-bin
	rm -f core core.* *.o a.out *~ numtbl.h *.i *.s

CC=gcc
CFLAGS=-g -Wall -g3 -O0
LDFLAGS=

endian: endian.c
	gcc -Wall -g3 -O0 -o $@ $^

ext2fs_test: ext2fs_test.c
	gcc -Wall -g3 -O0 -o $@ $^ -lext2fs

kudzu_loader-test: kudzu_loader-test.c
	gcc -Wall -g3 -O0 -static -o $@ $^ -lkudzu_loader -lpci -lz

pump-test: pump-test.c
	diet gcc -Wall -g3 -O0 -static -o $@ $^ -lpump-diet

librpm-readheader: librpm-readheader.c
	gcc -Wall -g3 -O0 -L/usr/X11R6/lib -lrpm -o $@ $^

librpm-install: librpm-install.c
	gcc -Wall -g3 -O0 -lrpm -o $@ $^

xlib_bitmap_threads: xlib_bitmap_threads.c
	gcc -Wall -g3 -O0 -L/usr/X11R6/lib -lX11 -lXpm -lpthread -o $@ $^

xlib_bitmap: xlib_bitmap.c
	gcc -Wall -g3 -O0 -L/usr/X11R6/lib -lX11 -lXpm -lpthread -o $@ $^

stdio: stdio.c

WCSTDIO_LDFLAGS=$(DEF_LDFLAGS) -lnss
wcstdio: wcstdio.c

suidtest: suidtest.c
	$(CC) \
	 -g3 -O0 -Wall -o $@ $^
	chown root.root $@
	chmod 4755 $@

test: test.c
	$(CC) \
	 $(shell pkg-config --cflags glib-2.0) \
	 $(shell pkg-config --libs glib-2.0) \
	 -g3 -O0 -Wall -o --save-temps $@ $^

gtkhello: gtkhello.c
	$(CC) \
	 $(shell pkg-config --cflags glib-2.0) \
	 $(shell pkg-config --libs glib-2.0) \
	 $(shell pkg-config --cflags gtk+-2.0) \
	 $(shell pkg-config --libs gtk+-2.0) \
	 -g3 -O0 -Wall -o $@ $^

curltest: curltest.c
	$(CC) -lcurl -g3 -O0 -Wall -o $@ $^

matrixmult: matrixmult.o
	$(CC) -Wall -g3 -O0 -lpthread -o $@ $^ $(LDFLAGS)

hello: hello.o
	$(CC) -o $@ $^ $(LDFLAGS)

hello.o: hello.c
	$(CC) -c $^ $(CFLAGS)

sh: sh.o
	$(CC) -o $@ $^ $(LDFLAGS)

sh.o: sh.c
	$(CC) -Dminsh_main=main -c $^ $(CFLAGS)

mknod.o: mknod.c
	$(CC) -c -o $@ $^ $(CFLAGS) $(LDFLAGS)

GSTR_CFLAGS=$(DEF_CFLAGS) -I/usr/lib/glib/include/
GSTR_LDFLAGS=$(DEF_LDFLAGS) -lglib
gstr: gstr.c
	gcc $(shell glib-config --cflags) -lglib -lgthread -o $@ $^

mygstring: mygstring.c
	$(CC) \
	 $(shell pkg-config --cflags gobject-2.0) \
	 $(shell pkg-config --libs gobject-2.0) \
	 -g3 -O0 -Wall -o $@ $^

glist: glist.c
	gcc $(shell glib-config --cflags) -lglib -lgthread -o $@ $^

lvm_test: lvm_test.c
	$(CC) -llvm-iop10 -Dminsh_main=main -c $^ $(CFLAGS)

pthread: pthread.o
	gcc $(PTHREAD_LIB) -O0 -g -o $@ $^

ptrace: ptrace.c
	make -f ptrace.mak $@

# With clone(2)
clone.o: clone.c
	gcc -g -DUSE_CLONE -c -o $@ $^

clone: clone.o
	gcc -o $@ $^

# Simulates clone(2) with Pthreads
pclone.o: clone.c
	gcc -Wall -g -c -o $@ $^

pclone: pclone.o
	gcc $(PTHREAD_LIB) -o $@ $^

strace: strace.o
	gcc -o $@ $^

fclone: fclone.o
	gcc -o $@ $^

gthread: gthread.c
	gcc $(shell glib-config --cflags) -lglib -lgthread -o $@ $^

gthread2: gthread2.c
	$(CC) \
	 $(shell pkg-config --cflags gobject-2.0 gthread-2.0) \
	 $(shell pkg-config --libs gobject-2.0 gthread-2.0) \
	 -g3 -O0 -Wall -o $@ $^

likely: likely.o
	gcc -o $@ $^

ped: ped.c
	gcc -o $@ $^ -lparted

str_test: str_test.c str.c
	gcc -Wall -o $@ $^

str_ptr_test: str_ptr.c str_ptr_test.c
	gcc -Wall -o $@ $^

str_cpp_test: str_cpp_test.c
	gcc -Wall -o $@ $^

static: static.c
	gcc -static -o $@ $^

dynamic: dynamic.c
	#gcc --verbose -Wl,--verbose,-Map,dynamic.map -o $@ $^
	gcc --verbose -Wl,-Map,dynamic.map -o $@ $^

comp: comp.c
	gcc -lm -o $@ $^

popttest: popttest.c
	gcc -lpopt -o $@ $^

sincos: sincos.c
	gcc -D_GNU_SOURCE -Wall -lm -o $@ $^

trigraph: trigraph.c
	gcc -ansi -o $@ $^

etest: etest.c exception.c
	gcc -g -O0 -o $@ $^

libexif_test: libexif_test.c
	gcc -g -O0 -lexif -o $@ $^

test_h: test.h
	cpp -P -undef -D_MINIMUM_ $^

newt_test: newt_test.c
	gcc -g -O0 -lnewt -lslang -o $@ $^ -ldistro

long_test: long_test.c
	gcc -g -O2 -O2 -O2 -O2 -O2 -O2 -O2  -o $@ $^

pamtest: pamtest.c
	gcc -Wall -g -O0 -lpam -lpam_misc -o $@ $^

xlibdraw: xlibdraw.o
	gcc -Wall  $^ -lX11 -L/usr/X11R6/lib/ -o $@

xlibdraw.o: xlibdraw.c
	gcc -Wall -I/usr/X11R6/include/ -O0 -g -c $^

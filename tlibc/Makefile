CC=gcc
CFLAGS=-Wall
LDFLAGS=
USE_STATIC=yes
USE_TLIBC=yes

ifeq ($(USE_STATIC), yes)
  STATIC=-static
else
  STATIC=
endif

ifeq ($(USE_TLIBC), yes)
  GCC_PATH=$(shell LANG=C LC_ALL=C gcc -print-search-dirs | grep ^install: | \
   sed -e "s/^install: *//" )
  CFLAGS+=-nostdinc -Os -Wall -I$(GCC_PATH)/include -I/usr/include/tlibc
  LDFLAGS+=-nostdlib -s /usr/lib/tlibc/crt0.o -L/usr/lib/tlibc \
   -L$(GCC_PATH) -lc -lgcc $(STATIC)
endif

insmod.static: insmod.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lmodutils -lc -lgcc

newt.static: newt.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lmodutils -lnewt -lslang -ldistro -lc -lgcc 

clean:
	rm -f core *.o a.out *~ hello stat insmod.static

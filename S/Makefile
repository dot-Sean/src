all:

GCC_PATH=$(shell gcc -print-search-dirs | grep ^install: | \
 sed -e "s/^install: *//" )

write: write.o
	gcc -nostdlib -m elf_i386 -static \
	 /usr/lib/crt1.o \
	 /usr/lib/crti.o \
	 /usr/lib/crtn.o \
	 $^ -lc -lgcc -o $@

write.o: write.S
	as -a --gstabs -o write.o write.S

test: test.c
	gcc -g -Wall -save-temps -o $@ $^

clean:
	rm -f write *.o *~ test *.i *.o *.s a.out


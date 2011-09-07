CFLAGS=-Wall

ptrace: ptrace.o
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f core *.o a.out *~ ptrace numtbl.h

numtbl.h: /usr/include/asm/unistd.h
	perl -e 'while (<>) { if (s/^#define __NR_([_a-zA-Z0-9]+)[ \t]*([0-9][0-9]*).*/asz_[\2] = "\1";/g) { print } }' < $^ > $@

ptrace.o: ptrace.c numtbl.h


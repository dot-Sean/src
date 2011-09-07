STDINCS=syscall.inc cchars.inc

all:

syscall.inc: syscall.inc.in /usr/include/asm-i386/unistd.h
	cpp -P $< > $@

hello.o: hello.asm $(STDINCS)
	nasm -f elf -o $@ $<

hello: hello.o
	ld -s -o $@ $<

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

clean-by-name:
	rm -f core *.o a.out *~ *.i syscall.inc

clean: clean-by-name clean-bin

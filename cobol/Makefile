all:

CFLAGS:=-Wall
LDFLAGS:=$(LDFLAGS) -lcob

#%.c: %.cob
#	cobc -C -main -o $@ $^
#	#cobc -C -o $@ $^

hello: hello.cob
	cobc $^ -o $@

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
	rm -f core *.o a.out *~ numtbl.h *.i *.s *.c


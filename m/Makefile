all:

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
	rm -f core *.o a.out *~ numtbl.h *.i *.s

clean: clean-by-name clean-bin

%.o: %.m
	gcc -Wall -c -o $@ $^

hello: hello.o mystr.o
	gcc -Wall -o hello -lobjc hello.o mystr.o

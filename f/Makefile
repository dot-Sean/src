all:

stdio: stdio.f
	g77 -o $@ $^

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
	rm -f *~ *.o stdio

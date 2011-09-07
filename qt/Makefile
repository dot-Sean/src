clean:
	rm -f core *.o a.out *~ hello stat
	for i in *; \
	do \
	  if [ -d $$i -a -e $$i/Makefile ]; \
	  then \
	    make -C $$i clean; \
	  fi \
	done


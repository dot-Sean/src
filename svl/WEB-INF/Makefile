all:
	make -C classes all
	make -C lib all
	make -C tld all

	for i in /usr/share/struts/*.tld ; \
	do \
	  ln -sf $$i $$(basename $$i) ; \
	done

clean:
	rm -f *~
	make -C classes clean
	make -C lib clean
	make -C tld clean

	for i in *.tld ; \
	do \
	  if test -L $$i ; \
	  then \
	    rm -f $$i; \
	  fi \
	done 

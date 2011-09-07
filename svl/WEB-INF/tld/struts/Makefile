all:
	for i in /usr/share/struts/*.tld ; \
	do \
	  cp -f $$i $$(basename $$i) ; \
	done

clean:
	rm -f *~ *.tld

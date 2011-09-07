all: 
	for i in \
	 struts \
	 commons-beanutils \
	 commons-digester \
	 commons-fileupload \
	 commons-validator ; \
	do \
	  ln -sf $$(build-classpath $$i) \
	   $$(basename $$(build-classpath $$i)) ; \
	done

clean:
	for i in *.jar ; \
	do \
	  if test -L $$i ; \
	  then \
	    rm -f $$i ; \
	  fi \
	done

SUBDIRS = lib python tools

clean-local:
	rm -f *~ core *.tar.gz *.spec

force:
.PHONY: force

@PACKAGE@.spec: force
	sed -e " \
	 s/__NAME__/@PACKAGE@/; \
         s/__VERSION__/@VERSION@/; \
         s/__RELEASE__/@RELEASE@/; \
         s/// " @PACKAGE@.spec.in > $@
	cat ChangeLog >> $@

spec: @PACKAGE@.spec

@PACKAGE@-@VERSION@.tar.gz: Makefile force
	root=./@PACKAGE@-@VERSION@; \
	rm -fr $$root; \
	tar cf - * | (mkdir -p $$root; cd $$root; tar xf -); \
	make -C $$root distclean @PACKAGE@.spec; \
	tar zcf $@ $$root; \
	rm -fr $$root

tarball: @PACKAGE@-@VERSION@.tar.gz

rpm: @PACKAGE@-@VERSION@.tar.gz
	rpm -ta --clean $^

srpm: @PACKAGE@-@VERSION@.tar.gz
	rpm -ts --clean $^

# --------------------------------------------------------------------

# Files not to be imported to repository. These can be changed when
# you execute autogen with diffeernt versions of autotools

LIBTOOLIZE_GENERATES = config.guess config.sub ltmain.sh 
AUTOHEADER_GENERATES = config.h.in
ACLOCAL_GENERATES = aclocal.m4
AUTOMAKE_GENERATES = COPYING INSTALL ansi2knr.c ansi2knr.1 \
 compile config.guess config.sub depcomp elisp-comp \
 install-sh mdate-sh missing mkinstalldirs \
 py-compile texinfo.tex ylwrap Makefile.in
AUTOCONF_GENERATES = configure autom4te.cache/
PODYN = po/*.gmo po/stamp-po po/*.pot

reposclean: distclean
	rm -fr $(PODYN)
	rm -fr $(AUTOCONF_GENERATES)
	rm -fr $(AUTOHEADER_GENERATES)
	for dir in $(SUBDIRS) ; \
	do \
	  if test $$dir != "intl" ; \
	  then \
	    rm -f $$dir/Makefile.in ; \
	  fi \
	done
	rm -fr $(AUTOMAKE_GENERATES)
	rm -fr $(ACLOCAL_GENERATES)
	rm -fr $(LIBTOOLIZE_GENERATES)

# Remove the following lines and orig/ directory after the project has
# started.

GETTEXTIZE_GENERATES = ABOUT-NLS mkinstalldirs config.rpath po/ m4/ intl/
GETTEXT_H = gettext.h tools/gettext.h
AUTOMAKE_REQUIRES = NEWS README AUTHORS ChangeLog
COPIED = Makefile.am configure.in

spotless: reposclean
	rm -fr $(GETTEXTIZE_GENERATES)
	rm -fr $(GETTEXT_H)
	rm -fr $(AUTOMAKE_REQUIRES)
	rm -fr $(COPIED)

# --------------------------------------------------------------------

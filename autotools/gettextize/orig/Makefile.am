bin_PROGRAMS = mytest
mytest_SOURCES = mytest.c
mytest_CFLAGS = -Ddatadir=\"$(datadir)\"

clean-local:
	rm -f *~

SUBDIRS =

# --------------------------------------------------------------------

spotless: distclean
	@echo d: libtoolize
	rm -f config.guess config.sub ltmain.sh
	@echo d: gettextize
	rm -fr ABOUT-NLS mkinstalldirs config.rpath po/ m4/ intl/
	rm -f gettext.h
	@echo d: autoheader
	rm -f config.h.in
	@echo d: aclocal
	rm -fr aclocal.m4 autom4te.cache/
	@echo d: necessary files for automake
	rm -f NEWS README AUTHORS ChangeLog
	@echo d: automake '(configure.in)'
	rm -f install-sh missing compile
	@echo d: automake '(Makefile.am)'
	rm -f COPYING INSTALL depcomp
	@echo d: automake
	rm -f Makefile.in
	for dir in $(SUBDIRS) ; \
	do \
	  rm -f $$dir/Makefile.in ; \
	done
	@echo d: autoconf
	rm -f configure
	@echo d: copied
	rm -f Makefile.am configure.in

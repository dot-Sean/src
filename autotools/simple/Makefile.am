SUBDIRS = sub_0 python sub_1

bin_PROGRAMS = hello
hello_SOURCES = hello.c

if FEATURE_ENABLED
noinst_PROGRAMS = hello2
hello2_SOURCES = hello2.c
endif

hoge_SCRIPTS = test.sh
hogedir = @hogedir@

clean-local:
	rm -f *~

# --------------------------------------------------------------------

spotless: distclean
	@echo d: libtoolize
	rm -f config.guess config.sub ltmain.sh
	@echo d: autoheader
	rm -f config.h.in
	@echo d: aclocal
	rm -fr aclocal.m4 autom4te.cache/
	@echo d: necessary files for automake
	rm -f NEWS README AUTHORS ChangeLog
	@echo d: automake '(configure.in)'
	rm -f install-sh missing
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

hoge:
	echo hoge_value: @hoge_value@
	echo with_fuga: @with_fuga@
	echo foodir: @foodir@
	echo PYTHON: $(PYTHON), @PYTHON@
	echo PYTHON_VERSION: $(PYTHON_VERSION), @PYTHON_VERSION@
	echo PYTHON_PREFIX: $(PYTHON_PREFIX), @PYTHON_PREFIX@
	echo PYTHON_EXEC_PREFIX: $(PYTHON_EXEC_PREFIX), @PYTHON_EXEC_PREFIX@
	echo PYTHON_PLATFORM: $(PYTHON_PLATFORM), @PYTHON_PLATFORM@
	echo pythondir: $(pythondir), @pythondir@
	echo pkgpythondir: $(pkgpythondir), @pkgpythondir@
	echo pyexecdir: $(pyexecdir), @pyexecdir@
	echo pkgpyexecdir: $(pkgpyexecdir), @pkgpyexecdir@

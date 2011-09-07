INCLUDES = -I$(PYTHON_INCLUDES) -I$(top_srcdir)/lib/

python_LTLIBRARIES = hellosub.la

hellosub_la_SOURCES = hellosub.c
hellosub_la_LDFLAGS = -module -avoid-version
hellosub_la_LIBADD = \
 -L$(top_builddir)/lib/.libs \
 $(top_builddir)/lib/libhello.la

python_PYTHON = hello.py

clean-local:
	rm -f *~ *.pyc

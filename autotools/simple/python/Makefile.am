AUTOMAKE_OPTIONS = foreign

INCLUDES = -I$(PYTHON_INCLUDES) -I$(top_srcdir)/sub_0

python_LTLIBRARIES = mylib.la

mylib_la_SOURCES = pymylib.c
mylib_la_LDFLAGS = -module -avoid-version
mylib_la_LIBADD = \
 -L$(top_builddir)/sub_0/.libs \
 $(top_builddir)/sub_0/libmylib.la

clean-local:
	rm -f *~

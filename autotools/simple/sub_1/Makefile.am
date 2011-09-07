INCLUDES = -I$(top_srcdir)/sub_0

bin_PROGRAMS = mytest2
bin_SCRIPTS = mytest2-wrapper

mytest2_SOURCES = mytest2.c
mytest2_LDADD = \
 -L$(top_builddir)/sub_0/.libs \
 $(top_builddir)/sub_0/libmylib.la

clean-local:
	rm -f *~

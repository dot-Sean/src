INCLUDES = -I$(top_srcdir)/lib/

bin_PROGRAMS = hello

hello_CFLAGS = -Ddatadir=\"$(datadir)\"
hello_SOURCES = hello.c
hello_LDADD = \
 -L$(top_builddir)/lib/.libs \
 $(top_builddir)/lib/libhello.la

man_MANS = hello.1

clean-local:
	rm -f *~

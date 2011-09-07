AUTOMAKE_OPTIONS = foreign

# Prefixes are the destination directories:
#  programs: bin, sbin, libexec, sysconf, localstate, lib, pkglib
#  data: data, info, man, include, oldinclude, pkgdata, pkginclude
lib_LTLIBRARIES=libhello.la

libhello_la_SOURCES = hello.c
libhello_la_LDFLAGS = -version-info @LIBHELLO_VERSION_INFO@

include_HEADERS = hello.h
#nobase_include_HEADERS = hello/hello.h

man_MANS = hello.3

noinst_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = -lhello

clean-local:
	rm -f *~

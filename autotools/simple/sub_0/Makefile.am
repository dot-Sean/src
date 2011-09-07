AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES=libmylib.la
libmylib_la_SOURCES = mylib.c
libmylib_la_LDFLAGS = -version-info @MYLIB_VERSION_INFO@

noinst_PROGRAMS = mytest

mytest_SOURCES = mytest.c
mytest_LDADD = -lmylib

clean-local:
	rm -f *~

hoge:
	echo d: @hoge_value@

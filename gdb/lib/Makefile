CFLAGS=-g -Wall -fPIC

all: slib dlib

slib: libstest.a

dlib: libdtest.so

# archive(member)
libstest.a: libstest.a(test1.o) libstest.a(test2.o)
	ranlib $@

libdtest.so: test1.o test2.o
	$(CC) $(LDFLAGS) -shared -o $@ $^

clean:
	rm -f *.o *.a *~ *.so

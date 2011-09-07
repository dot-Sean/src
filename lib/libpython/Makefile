PYPREFIX=$(shell python -c "import distutils.sysconfig; print distutils.sysconfig.PREFIX")
PYVER=$(shell python -c "import sys; print sys.version[:3]")

CFLAGS=-g -Wall -I$(PYPREFIX)/include/python$(PYVER)/
LDFLAGS=-L$(PYPREFIX)/lib/python$(PYVER)/config/
LIBS=-ldl -lpthread -lutil -lm -lpython$(PYVER)

all:
	echo d: $(CFLAGS) $(LDFLAGS)

test: test.o 
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

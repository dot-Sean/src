all: _pygettext.so

PYINCDIR=$(shell python -c "import distutils.sysconfig; print distutils.sysconfig.get_python_inc()")

clean:
	rm -fr *~ *.o *.so *.pyc *.pyo *.jpg *.dat

_pygettext.so: _pygettext.c
	gcc -Wall -o _pygettext.o -fPIC -I$(PYINCDIR) -c _pygettext.c
	gcc -o _pygettext.so -shared _pygettext.o

mypyobject.so: mypyobject.c
	gcc -Wall -o mypyobject.o -fPIC -I$(PYINCDIR) -c mypyobject.c
	gcc -o mypyobject.so -shared mypyobject.o

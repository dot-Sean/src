PYINC=$(shell python -c 'import distutils.sysconfig; \
 print distutils.sysconfig.get_python_inc()' )
PLINC=$(shell perl -e 'use ExtUtils::Embed; perl_inc()')
CFLAGS=-I$(PYINC) $(PLINC)
CXXFLAGS=-I$(PYINC) $(PLINC) -fpic  -Dexplicit=
LDFLAGS=-shared

#PLNAME=ccprog
PLNAME=PlCcprog

# --------------------------------------------------------------------

PYSCR=pycprog.py pyccprog.py
PYMOD=_pycprog.so _pyccprog.so

PLSCR=PlCprog.pm $(PLNAME).pm
PLMOD=PlCprog.so $(PLNAME).so

TARGET=$(PYMOD) $(PLMOD)

all: $(TARGET)

# --------------------------------------------------------------------

pycprog_wrap.c: cprog.h cprog.c
	swig -o $@ -module pycprog -Wall -python $<

_pycprog.so: cprog.o pycprog_wrap.o
	gcc $(LDFLAGS) $^ -o $@

# python -c 'import pycprog; print pycprog.get_time()'

# --------------------------------------------------------------------

plcprog_wrap.c: cprog.h cprog.c
	swig -o $@ -module PlCprog -Wall -perl5 $<

PlCprog.so: cprog.o plcprog_wrap.o
	gcc $(LDFLAGS) $^ -o $@

# perl -e 'use PlCprog; print PlCprog::get_time() . "\n"'

# --------------------------------------------------------------------

pyccprog_wrap.cc: ccprog.h ccprog.cc
	# http://swig.sourceforge.net/Doc1.3/SWIG.html
	swig -Wall -module pyccprog -python -o $@ -c++ $<

_pyccprog.so: ccprog.o pyccprog_wrap.o
	g++ $(LDFLAGS) $^ -o $@

# python -c 'import pyccprog; o = pyccprog.MyStr("ABC"); print o.get()'

# --------------------------------------------------------------------

plccprog_wrap.cc: ccprog.h ccprog.cc
	# http://swig.sourceforge.net/Doc1.3/SWIG.html
	swig -proxy -shadow -module $(PLNAME) -Wall -perl5 -c++ -o $@ $<

$(PLNAME).so: ccprog.o plccprog_wrap.o
	g++ $(LDFLAGS) $^ -o $@

# perl -e 'use PlCcprog; $o = new PlCcprog::MyStr("ABC"); print $o->get() . "\n"'

# --------------------------------------------------------------------

clean:
	rm -f *.so *~ *.o *.pyc *.pyo $(TARGET) *_wrap.c *_wrap.cc \
	 $(PYSCR) $(PYSO) $(PLSCR) $(PLSO)

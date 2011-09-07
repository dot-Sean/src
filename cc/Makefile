CXXFLAGS=-Wall -g -O0

all:

clean-bin:
	for i in *; \
	do \
	  if file $$i 2>&1 | grep -e '\<ELF\>' -e '\<PE\>' > /dev/null 2>&1; \
	  then \
	    echo Removing executable \"$$i\".; \
	    rm -f $$i; \
	  fi \
	done

clean: clean-bin clean-qttest
	rm -f core *.o a.out *~ numtbl.h *.i *.s *.ii

internal:
	g++ internal.cc /usr/lib/gcc-lib/i586-pc-linux/3.0.4/libstdc++.a -o internal

xerces-c: xerces-c.o
	g++ -lxerces-c -o $@ $^

wxtest: wxtest.cpp
	g++ -b i586 -O0 -g3 `wx-config --cxxflags` `wx-config --libs` -o $@ $^

hellothreads: hellothreads.cpp
	g++ -O0 -g3 -lboost_thread -o $@ $^

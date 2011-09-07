CXX=g++
CXXFLAGS=-Wall -Wno-format $(shell pkg-config --cflags qt-mt)

qttest: qttest.o moc_testform.o testform.o moc_testformimpl.o testformimpl.o
	g++ -Wall $(shell pkg-config --libs qt-mt) -o $@ $^

qttest.cpp: testform.h

testform.h: testform.ui
	uic -o $@ $^

testform.cpp: testform.h testform.ui
	uic -impl $^ -o $@

moc_testform.cpp: testform.h
	moc $^ -o $@

moc_testformimpl.cpp: testformimpl.h
	moc $^ -o $@

clean:
	rm -f *~ *.o qttest testform.h testform.cpp moc_*.cpp

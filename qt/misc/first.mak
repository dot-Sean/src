TARGET=first
OBJECTS=first.o

CXX=g++
LD=g++

QTDIR=/usr/lib/qt
CXXFLAGS=-I$(QTDIR)/include
LDFLAGS=-L$(QTDIR)/lib -lqt

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	-rm -f $(TARGET) $(OBJECTS) *~ core



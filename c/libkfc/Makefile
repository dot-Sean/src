VERSION=1.08

OBJS=str.o re.o cmd.o fs.o err.o mem.o log.o dic.o tree.o vec.o gz.o 
# tree2.o stk.o 

NAME=libkfc
SLIB=$(NAME).a
DLIB=$(NAME).so.$(VERSION)
TARGET=$(SLIB) $(DLIB)
PREFIX=/usr/local
DEP=DEPINFO
CC=gcc
CFLAGS=-g -Wall
CPP=cpp
SOURCES=$(subst .o,.c, $(OBJS))
LIBS=-lz -lxml
#LIBS=

all: $(TARGET)

libkfc.a: $(OBJS)
	ar r $@ $^

libkfc.so.$(VERSION): $(OBJS)
	$(CC) -fpic -shared -o $@ $^

install: all
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/lib
	install -m 755 libkfc.so.$(VERSION) libkfc.a $(PREFIX)/lib
	ln -sf libkfc.so.$(VERSION) $(PREFIX)/lib/libkfc.so
	mkdir -p $(PREFIX)/include
	install -m 644 *.h $(PREFIX)/include
	if [ -x /sbin/ldconfig ]; then /sbin/ldconfig || true; fi

clean:
	rm -f $(TARGET) $(OBJS) $(DEP) *~ a.out core test test.o \
	 *.tar.gz *.spec *.so.*

test: test.o $(SLIB)
	$(CC) $(LIBS) -o $@ $^
# --------------------------------------------------------------------
dep:
	rm -f $(DEP)
	for i in $(SOURCES); do $(CPP) -M $$i >> $(DEP); done

ifeq ($(DEP),$(wildcard $(DEP)))
  include $(DEP)
endif                                           
# --------------------------------------------------------------------
HOUR=$(shell date --universal +%H)
MIN=$(shell date --universal +%M)
REVISION=$(shell printf "%02d" \
 `expr '(' '(' 60 '*' $(HOUR) '+' $(MIN) ')' '*' 100 ')' '/' 1440` )
SERIAL=$(shell date --universal +%Y%m%d)$(REVISION)

.PHONY: force
force:

$(NAME).spec: force
	sed -e " \
	 s/__NAME__/$(NAME)/; \
         s/__VERSION__/$(VERSION)/; \
         s/__RELEASE__/$(SERIAL)/; \
         s/__SERIAL__/$(SERIAL)/; \
         s/// " $(NAME).spec.in > $@

$(NAME)-$(VERSION).tar.gz: Makefile force
	root=./$(NAME)-$(VERSION); \
	rm -fr $$root; \
	tar cf - * | (mkdir -p $$root; cd $$root; tar xf -); \
	make -C $$root clean $(NAME).spec; \
	tar zcf $@ $$root; \
	rm -fr $$root

.PHONY: tarball
tarball: $(NAME)-$(VERSION).tar.gz

.PHONY: rpm
rpm: $(NAME)-$(VERSION).tar.gz
	rpm -ta $^

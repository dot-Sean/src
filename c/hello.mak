TARGET=hello
VERSION=1.0
PREFIX=/usr
POFILES=zh_CN.po zh_TW.po ja.po ko.po
OBJS=hello.c
# --------------------------------------------------------------------
CC=gcc
CFLAGS=
LDFLAGS=

LANGS=$(subst .po,,$(POFILES))
MOFILES=$(subst .po,.mo,$(POFILES))
SOURCES=$(subst .o,.c,$(OBJS))

.SUFFIXES: .po .mo

.po.mo:
	msgfmt -o $@ $<

all: $(TARGET) $(MOFILES)

messages.po: $(SOURCES)
	xgettext --output=$@ --keyword --keyword=_ --keyword=__ $^

update-po: messages.po
	for lang in $(LANGS); \
	do \
	  if [ -e $$lang.po ]; \
	  then \
	    mv $$lang.po $$lang.po.old; \
	    msgmerge $$lang.po.old $< > $$lang.po; \
	  else \
	    cp $< $$lang.po; \
	  fi \
	done

clean:
	rm -f $(TARGET) $(OBJS) *~ core *.po.old *.mo \
	 messages.po

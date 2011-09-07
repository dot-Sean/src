NAM_VER0=rpmtest-1.0
NAM_VER1=rpmtest-1.1

all: rpm

clean:
	rm -f *~ */*.spec *.tar.gz

HOUR=$(shell date --universal +%H)
MIN=$(shell date --universal +%M)
REVISION=$(shell printf "%02d" \
 `expr '(' '(' 60 '*' $(HOUR) '+' $(MIN) ')' '*' 100 ')' '/' 1440` )
SERIAL=$(shell date --universal +%Y%m%d)$(REVISION)

.PHONY: force

force:

$(NAM_VER0)/rpmtest.spec: rpmtest.spec.in
	sed -e " \
	 s/__NAME__/$(NAME)/; \
         s/__VERSION__/1.0/; \
         s/__RELEASE__/1/; \
         s/__SERIAL__/10/; \
         s/// " $< > $@

$(NAM_VER0).tar.gz: $(NAM_VER0)/rpmtest.spec force
	make -C $(NAM_VER0) clean
	rm -f $@
	tar zcvf $@ $(NAM_VER0)

$(NAM_VER1)/rpmtest.spec: rpmtest.spec.in
	sed -e " \
	 s/__NAME__/$(NAME)/; \
         s/__VERSION__/1.1/; \
         s/__RELEASE__/1/; \
         s/__SERIAL__/11/; \
         s/// " $< > $@

$(NAM_VER1).tar.gz: $(NAM_VER1)/rpmtest.spec force
	make -C $(NAM_VER1) clean
	rm -f $@
	tar zcvf $@ $(NAM_VER1)

.PHONY: tarballs

tarballs: $(NAM_VER0).tar.gz $(NAM_VER1).tar.gz

srpms: tarballs
	rpm -ts $(NAM_VER0).tar.gz $(NAM_VER1).tar.gz

rpms: tarballs
	rpm -ta $(NAM_VER0).tar.gz $(NAM_VER1).tar.gz

srpm: $(NAM_VER0).tar.gz
	rpm -ts $<

rpm: $(NAM_VER0).tar.gz
	rpm -ta $<


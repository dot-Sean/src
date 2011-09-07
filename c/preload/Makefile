TARGETS=test_preload libpreload.so

all: $(TARGETS)

clean:
	rm -f $(TARGETS) *.o *.so *~

test:
	LD_PRELOAD=$$PWD/libpreload.so ./test_preload

test_preload: test_preload.c

libpreload.so: preload.c
	gcc -shared -fPIC -ldl -o $@ $^

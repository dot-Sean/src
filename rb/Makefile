all:

RUBY_INCLUDE_DIR=$(shell ruby -rrbconfig -e 'puts Config::CONFIG["archdir"]')

clean:
	rm -f *~ a.out core libruby_test *.o

# Requires ruby-devel
libruby_test: libruby_test.c
	gcc -I$(RUBY_INCLUDE_DIR) -o $@ -g -ldl -lcrypt -lruby $^

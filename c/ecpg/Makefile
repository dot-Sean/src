ECPG=/usr/local/pgsql/bin/ecpg
CFLAGS=-I/usr/local/pgsql/include -L/usr/local/pgsql/lib -lecpg

ecpgtest: ecpgtest.c

%.c: %.pgc
	$(ECPG) $<

test: ecpgtest
	LD_LIBRARY_PATH=/usr/local/pgsql/lib/ ./ecpgtest

clean:
	rm -f test ecpgtest *~ ecpgtest.c



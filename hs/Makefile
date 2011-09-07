test:
	hugs +l test.hs

sayhello:
	./hello World

hi: hi.hs
	ghc --make $^ -o $@

sayhi: hi
	./hi World

clean:
	rm -f hi *~
	rm -f hi.hi # ?
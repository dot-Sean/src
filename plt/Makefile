%.png: %.plt
	cat $^ | gnuplot | convert -resize 50% eps:- $@

all:

clean:
	rm -f *~ *.eps *.png

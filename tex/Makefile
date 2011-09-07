%.dvi: %.tex
	platex $^

%.ps: %.dvi
	dvips $^ -o $@

%.eps: %.dvi
	dvips -E $^ -o $@

%.pdf: %.dvi
	dvipdf $^ $@

%.png: %.dvi
	dvips -y 5000 -q -E $^ -o - | convert -resize 35% eps:- $@

all:

clean:
	rm -f *~ *.aux *.dvi *.log *.ps *.eps *.pdf


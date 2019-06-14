TEX	= latex -shell-escape
DVIPS	= dvips
DVIPDF  = dvipdft
XDVI	= xdvi -gamma 4
GH		= gv

EXAMPLES = $(wildcard *.h)
SRC	:= $(shell egrep -l '^[^%]*\\begin\{document\}' *.tex)
TRG	= $(SRC:%.tex=%.dvi)
PSF	= $(SRC:%.tex=%.ps)
PDF	= $(SRC:%.tex=%.pdf)

all: writeup

writeup:
	latex main.tex
	dvips -R -Poutline -t letter main.dvi -o main.ps
	ps2pdf main.ps
	chmod 777 main.pdf

turnin:
	rm -f *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

clean:
	rm -f *.pdf *.ps *.dvi *.out *.log *.aux *.bbl *.blg *.pyg

.PHONY: all show clean ps pdf showps

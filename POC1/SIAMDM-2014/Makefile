all: clean paper.pdf paper.ps
	
paper.pdf: paper.ps
	ps2pdf14 paper.ps

paper.ps: paper.dvi
	dvips -P pdf -t letter -o paper.ps paper.dvi

paper.dvi: paper.bbl
	latex paper.tex
	latex paper.tex

paper.bbl: paper.aux
	bibtex paper

paper.aux: paper.tex references.bib
	latex paper.tex

run: all 
	evince paper.ps &

clean:
	rm -f *.log *.aux *.bbl *.blg *.dvi *.ps *.pdf *.lot *.toc *.lof *.bak *~

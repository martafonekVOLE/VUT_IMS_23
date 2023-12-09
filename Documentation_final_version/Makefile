project = documentation
qpdf_flags = --linearize --replace-input

$(project):
	pdflatex $(project).tex
	bibtex $(project).aux
	pdflatex $(project).tex
	pdflatex $(project).tex
	qpdf $(qpdf_flags) $(project).pdf

clean:
	rm $(project).aux $(project).log $(project).out

vlna:
	vlna -r -l -v KkSsVvZzOoUuAaIi $(project).tex

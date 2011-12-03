# makefile
# Daniel Uber MCS 360 Fall 2011 Project 1
# build grocery inventory program

#default target
default: project1
	@head -n 15 README

run: project1
	./project1

# target in src copies binary here when done
project1: src
	$(MAKE) -C src all

# fixdoc adds options to Doxyfile
Doxyfile:
	doxygen -g
	./scripts/fixdoc

latex: Doxyfile
	doxygen

# alias targets
doc: manual.pdf
manual: manual.pdf

manual.pdf: latex
	$(MAKE) -C latex pdf
	mv latex/refman.pdf ./manual.pdf
	$(MAKE) -C latex clean

clean: docclean
	rm -f *~ *.o project1
	$(MAKE) -C src clean

docclean:
	rm -Rf latex html Doxyfile manual.pdf *.bak

# makefile
# Daniel Uber
# MCS 360 Project 4
CXXFLAGS+= -g -Wall -Werror
OBJECTS= main.o bstree.o menu.o
HEADERS= bstree.h menu.h
PROGRAM= runpr4id314

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

run: $(PROGRAM)
	./$(PROGRAM)

graphics:
	sh scripts/graphics.sh

doc:
	doxygen -g
	sh scripts/fixdoc.sh
	doxygen
	make -C latex refman.pdf
	mv latex/refman.pdf .

clean:
	rm -f *~ *.o $(PROGRAM)
	rm -f *.svg *.png *.dot
	rm -Rf html latex Doxyfile *.bak refman.pdf
# file makefile
# MCS360 project 2
# Daniel Uber
CXXOPTS+= -g -Wall -Werror -Wextra
HEADERS= poly.h menu.h
OBJECTS= poly.o menu.o main.o
PROGRAMNAME=p2

all: $(PROGRAMNAME)

$(PROGRAMNAME): $(OBJECTS) 
	$(CXX) $(CXXOPTS) -o $(PROGRAMNAME) $(OBJECTS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXOPTS) -c $<

run: $(PROGRAMNAME)
	./$(PROGRAMNAME)

doc:
	doxygen -g
	./fixdoc
	doxygen

clean:
	rm -f *~ *.bak *.o $(PROGRAMNAME)
	rm -Rf Doxyfile latex html

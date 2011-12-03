# makefile
# mcs 360 quiz 7
# Daniel Uber

HEADERS= quiz7.h stack.h delimiter.h
OBJECTS= quiz7.o main.o delimiter.o
SOURCES= main.cc quiz7.cc delimiter.cc stack.cc
CXXOPTS+= -Wall -Werror -Wextra -g
PROGNAME= quiz7

all: $(PROGNAME)

$(PROGNAME): $(HEADERS) $(OBJECTS)
	$(CXX) $(CXXOPTS) -o $(PROGNAME) $(OBJECTS)

%.o : %.cc $(HEADERS)
	$(CXX) $(CXXOPTS) -c $<

run:
	./$(PROGNAME)

clean:
	rm -f *~ *.o $(PROGNAME) *.gch
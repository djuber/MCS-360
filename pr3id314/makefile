# makefile
# mcs360 project 3
# Daniel Uber duber3@uic.edu

CXXFLAGS+= -g -Wall -Wextra -Werror 
PROGRAM=run314p3
OBJECTS=infixFormat.o main.o postfixFormat.o \
	postfixEval.o utilities.o
HEADERS=project3.h stack.h

# default target
all: $(PROGRAM)

# execution step
run: $(PROGRAM)
	./$(PROGRAM)

# force recompilation of main.cc 
# since test/run use different functions
rebuild:
	touch main.cc

# linking step
$(PROGRAM): rebuild $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

# general compilation step
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# delete intermediate file
clean:
	rm -f $(OBJECTS) $(PROGRAM) *~ Doxyfil*
	rm -Rf html latex

test: rebuild $(OBJECTS) test.h
	$(CXX) $(CXXFLAGS) -DTESTING -c main.cc
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)
	./$(PROGRAM)

doc:
	doxygen -g
	./fixdoc
	doxygen
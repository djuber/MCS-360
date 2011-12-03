# makefile
# mcs 360 quiz 12
# Daniel Uber
CXXFLAGS+= -Wall -Werror -Wextra -g
# what's this called?
PROGNAME=314quiz12
# where are the local declarations?
HEADERS=list.h
# what are the first set of binaries?
OBJECTS=main.o list.o
# and the second?
OBJECTS2=main.o list2.o

# what should make do?
all: $(PROGNAME) $(PROGNAME)-header

# what's the main program
$(PROGNAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGNAME) $(OBJECTS)

# what's the second main program?
$(PROGNAME)-header: $(OBJECTS2)
	$(CXX) $(CXXFLAGS) -o $(PROGNAME)-header $(OBJECTS2)

# how do I make a .o file?
%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# get rid of this junk!
clean:
	rm -f *.o *~ $(PROGNAME) $(PROGNAME)-header

# try the first program
run: $(PROGNAME)
	./$(PROGNAME)

#try the second program
run-header: $(PROGNAME)-header
	./$(PROGNAME)-header
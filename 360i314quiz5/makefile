# makefile
# mcs360 quiz 5 Daniel Uber
# read input file, produce output file

# CPPFLAGS is magic
CPPFLAGS+= -Wall -Werror -g -Wextra

# make knows how to compile source files if objects are dependencies
# and it automatically uses CPPFLAGS when it does this
OBJECTS= quiz5.o gcd.o Ratio.o 

all: quiz5

run: all
	./quiz5

quiz5: $(OBJECTS)
	g++ -o quiz5 -g $(OBJECTS)

clean:
	rm -f $(OBJECTS) *~

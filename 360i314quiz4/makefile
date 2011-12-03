#makefile
#Daniel Uber 
#makes programs from sources

CPPFLAGS+= -Wall -g -Wextra -Werror
OBJECTS= main.o quiz4.o


run: 360i314Quiz4
	@./360i314Quiz4
	@echo "Job Complete. Output in ./zsorted.dat"
	@echo
	@cat zsorted.dat

360i314Quiz4: $(OBJECTS)
	g++ $(CPPFLAGS) -o 360i314Quiz4 $(OBJECTS)

# make doesn't need targest for objects. Any object in a dependency list is automatically generated, with CPPFLAGS in effect.

clean:
	rm -f $(OBJECTS) 360i314Quiz4 zsorted.dat
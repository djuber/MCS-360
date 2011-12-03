# makefile : compiler driver
# Daniel Uber MCS 360 week 2 lab

C++OPTS= -Wall -Werror -Wextra -g
HEADERS= funcs.h score.h
OBJECTS= funcs.o score.o main.o

run: run314
	./run314

run314: $(OBJECTS)
	g++ $(C++OPTS) -o run314 $(OBJECTS) 

main.o: $(HEADERS) main.cc
	g++ $(C++OPTS) -c main.cc

funcs.o: $(HEADERS) funcs.cc
	g++ $(C++OPTS) -c funcs.cc

score.o: score.cc score.h
	g++ $(C++OPTS) -c score.cc

clean:
	rm -f *.o run314 score.dat *~

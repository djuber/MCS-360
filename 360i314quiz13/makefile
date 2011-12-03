#----------------------------------------------------
# makefile
#----------------------------------------------------
FLAGS= -g -Wall
run: tree.o main.o
	g++ $(FLAGS) -o run tree.o main.o
tree.o: tree.cc tree.h
	g++ $(FLAGS) -c tree.cc
main.o: main.cc tree.h
	g++ $(FLAGS) -c main.cc
clean:
	rm -f *.o run bugs
	rm -f *~




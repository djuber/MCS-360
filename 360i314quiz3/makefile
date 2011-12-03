# makefile
C++OPTS= -Wall -Wextra -Werror -g

run: all
	chmod +x runall.sh
	./runall.sh

all: q3p1.bin q3p2.bin q3p3.bin q3p4.bin

q3p1.bin: q3p1/q3p1.cc
	g++ $(C++OPTS) -o q3p1.bin q3p1/q3p1.cc

q3p2.bin: q3p2/q3p2.cc
	g++ $(C++OPTS) -o q3p2.bin q3p2/q3p2.cc

q3p3.bin: q3p3/q3p3.cc
	g++ $(C++OPTS) -o q3p3.bin q3p3/q3p3.cc

q3p4.bin: q3p4/q3p4.cc
	g++ $(C++OPTS) -o q3p4.bin q3p4/q3p4.cc

clean:
	rm -f *~ *.bin
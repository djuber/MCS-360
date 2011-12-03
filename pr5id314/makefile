# makefile

CXXFLAGS+= -g -Wall -Werror
OBJS=main.o hashchain.o hashfunction.o randwords.o
HEADERS=hashchain.h
PROGRAM=run

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJS) -lm -lcrypt

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(PROGRAM) $(OBJS) *~ randwords.txt

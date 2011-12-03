# makefile
# Daniel Uber
# build grocery store program

CXXFLAGS+= -Wall -Werror -Wextra -g
CXX=g++

# I could have used multiline escapes here
OBJECTS= project1.o month.o dollar.o item.o supplier-map.o
OBJECTS+= handleItemSale.o find.o dailyReport.o weeklyCheck.o 
OBJECTS+= monthlyUpdate.o loadInventory.o sortFile.o saveInventory.o
OBJECTS+= addItem.o editItem.o deleteItem.o

HEADERS= project1.h item.h supplier.h month.h dollar.h supplier-map.h
HEADERS+= isort.h find.h inventory.h InputValidator.h editItem.h

all: project1


project1: main.o project1.a
	$(CXX) $(CXXFLAGS) -o project1 main.o project1.a
	cp project1 ..

project1.a: $(HEADERS) $(OBJECTS)
	ar rcs project1.a $(OBJECTS)

# won't remove project1 binary from main directory, only here
clean:
	rm -f *.o *.a project1 *~

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<


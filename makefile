INC_DIR = include

all: hw1

hw1: main.o  
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o  -lgtest
else
	g++ -o hw1 main.o  -lgtest -lpthread
endif
	
main.o: main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif

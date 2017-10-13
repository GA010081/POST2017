all: hw3

hw3: Number.o Atom.o Struct.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3  Number.o Atom.o Struct.o -lgtest
else
	g++ -o hw3  Number.o Atom.o Struct.o -lgtest -lpthread
endif

Number.o: Number.cpp
	g++ -std=gnu++0x -c Number.cpp
Atom.o: Atom.cpp
	g++ -std=gnu++0x -c Atom.cpp
Struct.o: Struct.cpp utStruct.h utVariable.h
	g++ -std=gnu++0x -c Struct.cpp
clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3 utStruct
endif

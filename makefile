all: hw4 other

hw4: Number.o Atom.o MainList.o List.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 Number.o Atom.o MainList.o List.o -lgtest
else
	g++ -o hw4 Number.o Atom.o MainList.o List.o -lgtest -lpthread
endif

other:Number.o Atom.o Term.o List.o
ifeq (${OS}, Windows_NT)
	g++ -o other Number.o Atom.o Term.o List.o -lgtest
else
	g++ -o other Number.o Atom.o Term.o List.o -lgtest -lpthread
endif

Term.o : Term.cpp utTerm.h utVariable.h utStruct.h
	g++ -std=c++11 -c Term.cpp
Number.o: Number.cpp
	g++ -std=c++11 -c Number.cpp
Atom.o: Atom.cpp
	g++ -std=c++11 -c Atom.cpp
MainList.o:MainList.cpp utList.h
	g++ -std=c++11 -c MainList.cpp 
List.o: List.cpp
	g++ -std=c++11 -c List.cpp
clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif

all: hw5

utAtom: mainAtom.o atom.o
	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h 
	g++ -std=gnu++0x -c atom.cpp 
List.o:List.cpp list.h
	g++ -std=gnu++0x -c List.cpp
utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp


hw5: mainScanner.o atom.o List.o scanner.h utScanner.h utParser.h parser.h 
	g++ -o hw5 mainScanner.o atom.o List.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
		g++ -std=gnu++0x -c mainScanner.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner hw5
stat:
	wc *.h *.cpp

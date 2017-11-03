all: hw5


mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp
atom.o: atom.cpp atom.h variable.h 
	g++ -std=gnu++0x -c atom.cpp 
List.o:List.cpp list.h
	g++ -std=gnu++0x -c List.cpp
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
		g++ -std=gnu++0x -c mainScanner.cpp

hw5: mainScanner.o atom.o List.o scanner.h utScanner.h utParser.h parser.h 
	g++ -o hw5 mainScanner.o atom.o List.o -lgtest 
clean:
	rm -f *.o madRace utAtom utVariable utScanner hw5
stat:
	wc *.h *.cpp

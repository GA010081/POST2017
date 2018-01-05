all: hw7 hw8 shell
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp
#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp


hw7: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h struct.h 
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest -

shell:mainShell.o atom.o list.o struct.o
	g++ -o shell mainShell.o atom.o list.o struct.o -lgtest

hw8:  mainExpression.o atom.o list.o struct.o struct.h 
	g++ -o hw8 mainExpression.o atom.o list.o struct.o -lgtest 

mainExpression.o:mainExpression.cpp expression.h exception.h
	g++ -std=gnu++0x -c mainExpression.cpp

mainShell.o:mainShell.cpp
	g++ -std=gnu++0x -c mainShell.cpp

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp


clean:
	rm -f *.o  hw7 hw8 shell
stat:
	wc *.h *.cpp
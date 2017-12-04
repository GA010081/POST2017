all: hw7
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
	g++ -o hw7 mainIterator.o atom.o list.o struct.o -lgtest 



mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp


clean:
	rm -f *.o  hw7
stat:
	wc *.h *.cpp
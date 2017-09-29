all: hw2

hw2: Term.o  
ifeq (${OS}, Windows_NT)
	g++ -o hw2 Term.o  -lgtest
else
	g++ -o hw2 Term.o  -lgtest -lpthread
endif
	
Term.o: Term.cpp utTerm.h
	g++ -std=gnu++0x -c Term.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif

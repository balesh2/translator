CC=g++
CFLAGS=--std=c++11
EXE=trans

default: all 

scanner.o: scanner.cpp scanner.h enum.h token.h
	$(CC) $(CFLAGS) -c scanner.cpp -o scanner.o

all: translator.cpp scanner.o
	$(CC) $(CFLAGS) translator.cpp scanner.o -o $(EXE)

clean:
	rm scanner.o

cleanall: clean
	rm $(EXE) 

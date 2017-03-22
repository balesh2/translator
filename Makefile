CC=g++
CFLAGS=--std=c++11
EXE=translator

default: all 

scanner.o: scanner.cpp scanner.h enum.h token.h
	$(CC) $(CFLAGS) -c scanner.cpp -o scanner.o

treenode.o: treenode.cpp treenode.h
	$(CC) $(CFLAGS) -c treenode.cpp -o treenode.o

parser.o: parser.cpp parser.h scanner.o scanner.h enum.h token.h
	$(CC) $(CFLAGS) -c parser.cpp -o parser.o

checker.o: checker.cpp checker.h treenode.cpp treenode.h
	$(CC) $(CFLAGS) -c checker.cpp -o checker.o

all: translator.cpp scanner.o treenode.o parser.o checker.o
	$(CC) $(CFLAGS) translator.cpp scanner.o parser.o treenode.o checker.o -o $(EXE)

clean:
	rm scanner.o parser.o treenode.o checker.o 

cleanall: clean
	rm $(EXE) 

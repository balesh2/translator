CC=g++
CFLAGS=--std=c++11
EXE=trans

default: all 

scanner.o: scanner.cpp scanner.h enum.h token.h
	$(CC) $(CFLAGS) -c scanner.cpp -o scanner.o

treenode.o: treenode.cpp treenode.h
	$(CC) $(CFLAGS) -c treenode.cpp -o treenode.o

parser.o: parser.cpp parser.h scanner.o scanner.h enum.h token.h
	$(CC) $(CFLAGS) -c parser.cpp -o parser.o

all: translator.cpp scanner.o treenode.o parser.o
	$(CC) $(CFLAGS) translator.cpp scanner.o parser.o treenode.o -o $(EXE)

clean:
	rm scanner.o parser.o treenode.o

cleanall: clean
	rm $(EXE) 

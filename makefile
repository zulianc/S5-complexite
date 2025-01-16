all: avl.out

avl.out: avl.o
	g++ -g avl.o -o avl.out

avl.o: avl.cpp
	g++ -g -Wall -c avl.cpp
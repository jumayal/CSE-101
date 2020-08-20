#------------------------------------------------------------------------------
#  Juan Ayala, jumaayal
#  2020 Spring CSE101 PA3
#  Makefile for Arithmetic
#
#  make             makes FindPath
#  make clean       removes object files
#------------------------------------------------------------------------------
FindPath : FindPath.o Graph.o List.o
	gcc -std=c11 -Wall -o FindPath FindPath.o Graph.o List.o

GraphTest : GraphTest.o Graph.o List.o
	gcc -std=c11 -Wall -o GraphTest GraphTest.o Graph.o List.o

FindPath.o : FindPath.c Graph.h List.h
	gcc -std=c11 -Wall -c FindPath.c

GraphTest.o : GraphTest.c List.h
	gcc -std=c11 -Wall -c GraphTest.c

Graph.o: Graph.c Graph.h
	gcc -std=c11 -Wall -c Graph.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f FindPath GraphTest FindPath.o Graph.o GraphTest.o List.o

checkPath :
	valgrind --leak-check=full --show-leak-kinds=all ./FindPath in1 test_output
checkGraphTest :
	valgrind --leak-check=full ./GraphTest test_output

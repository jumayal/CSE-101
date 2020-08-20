#------------------------------------------------------------------------------
#  Juan Ayala, jumaayal
#  2020 Spring CSE101 PA4
#  Makefile for Arithmetic
#
#  make             makes FindComponents
#  make clean       removes object files
#------------------------------------------------------------------------------
FindComponents : FindComponents.o Graph.o List.o
	gcc -o FindComponents FindComponents.o Graph.o List.o
Test : GraphTest.o Graph.o List.o
	gcc -o Test GraphTest.o Graph.o List.o
FindComponents.o : FindComponents.c Graph.h
	gcc -c -std=c99 -Wall FindComponents.c

GraphTest.o: GraphTest.o Graph.h
	gcc -c -std=c99 -Wall GraphTest.c

Graph.o: Graph.c Graph.h List.h
	gcc -c -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f FindComponents Test FindComponents.o GraphTest.o Graph.o List.o

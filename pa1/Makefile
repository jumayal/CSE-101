#------------------------------------------------------------------------------
#  Juan Ayala, jumaayal
#  2020 Spring CSE101 PA1
#  Makefile for Lex
#
#  make             makes Lex
#  make clean       removes object files
#  make checkClient runs valgrind to check for memory errors in testClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c11 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c11 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c11 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c11 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkClient :
	valgrind --leak-check=full ./ListClient
	#valgrind --leak-check=full ListClient #Windows Version

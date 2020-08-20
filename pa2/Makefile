#------------------------------------------------------------------------------
#  Juan Ayala, jumaayal
#  2020 Spring CSE101 PA2
#  Makefile for Arithmetic
#
#  make             makes Lex
#  make clean       removes object files
#  make checkArithmetic runs valgrind to check for memory errors in Arithmetic
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o BigInteger.o List.o
	gcc -std=c11 -Wall -o Arithmetic Arithmetic.o BigInteger.o List.o

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	gcc -std=c11 -Wall -c Arithmetic.c

ListTest: ListTest.o List.o
	gcc -std=c11 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c11 -Wall -c ListTest.c

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	gcc -std=c11 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o : BigIntegerTest.c List.h
	gcc -std=c11 -Wall -c BigIntegerTest.c

BigInteger.o : BigInteger.c BigInteger.h
	gcc -std=c11 -Wall -c BigInteger.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f Arithmetic ListTest BigIntegerTest Arithmetic.o BigInteger.o BigIntegerTest.o ListTest.o List.o

checkArithmetic :
	valgrind --leak-check=full ./Arithmetic

checkBigInteger :
	valgrind --leak-check=full ./BigIntegerTest

checkList :
	valgrind --leak-check=full ./ListTest
	#valgrind --leak-check=full ListTest #Windows Version

/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA2
* Arithmetic.c
* Uses BigInteger for simple calculations
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"
#define MAX_LEN 100000


int main(int argc, char const *argv[]) {
  int count=0;
  FILE *in, *out;
  char line[MAX_LEN];

  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  //Open Input file and output file
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if( in==NULL ){ // If the input file doesnt exist -> exit
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if( out==NULL ){ //If the output file doesnt exist -> exit
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  // Count how many words are in the input file
  while( fgets(line, MAX_LEN, in) != NULL)  {
    count++;
  }
  if(count<1){ //If there are no words in file -> exit
    printf("There are no items");
    exit(1);
  }
  BigInteger A;
  BigInteger B;
  BigInteger Output;
  char nine[]="9";
  BigInteger nine_constant = stringToBigInteger(nine);
  char sixteen[] ="16";
  BigInteger sixteen_constant = stringToBigInteger(sixteen);

  fseek(in, 0, SEEK_SET);       //File reading cursor at the start of the file
  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  A= stringToBigInteger(line);
  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  B= stringToBigInteger(line);

  printBigInteger(out,A);
  fprintf(out,"\n\n");
  printBigInteger(out,B);
  fprintf(out,"\n\n");

  Output=sum(A,B);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");

  //A-B
  subtract(Output,A,B);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");

  //A-A
  subtract(Output,A,A);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");

  //3A-2B
   add(Output,A,sum(A,A));
   subtract(Output,Output,sum(B,B));
   printBigInteger(out,Output);
   fprintf(out,"\n\n");
  //AB
  multiply(Output,A,B);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");
  //fprintf(out,"\n\n");
  //AA
  multiply(Output,A,A);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");
  //BB
  multiply(Output,B,B);
  printBigInteger(out,Output);
  fprintf(out,"\n\n");
  //9A^4+16B^5
  BigInteger Apower=prod(A,prod(A,prod(A,A)));
  BigInteger Bpower= prod(B,prod(B,prod(B,prod(B,B))));
  add(Output,prod(nine_constant,Apower), prod(sixteen_constant,Bpower));
  printBigInteger(out,Output);
  fprintf(out,"\n\n");

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&Output);
  freeBigInteger(&nine_constant);
  freeBigInteger(&sixteen_constant);
  freeBigInteger(&Apower);
  freeBigInteger(&Bpower);
  fclose(in);
  fclose(out);
  return 0;
}

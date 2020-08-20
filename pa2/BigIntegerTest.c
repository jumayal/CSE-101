/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA2
*
*
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"


void printOutArithmetic(BigInteger A, BigInteger B, char* operator);
void expected(BigInteger A, BigInteger B);
void printVerb(BigInteger output, BigInteger A,BigInteger B, char* operator);
void testVerb(long output, long A, long B, char* operator);
void testNoun(long A, long B, char* operator);

int main(int argc, char* argv[]){
    BigInteger A = NULL;
    BigInteger B = NULL;
    BigInteger C = NULL;
    BigInteger D = NULL;

    BigInteger *pA=&A;
    BigInteger *pB =&B;
    BigInteger *pC =&C;
    BigInteger *pD =&D;

    *pA = stringToBigInteger("-111122223333");
    *pB = stringToBigInteger("-111122223333");
    //neg - neg = 0
    *pC = diff(*pA, *pB);
    if(sign(*pC) != 0) ;

    //neg - neg > 0
    freeBigInteger(pB);
    freeBigInteger(pC);
    *pB = stringToBigInteger("-112122223333");
    *pC = diff(*pA, *pB);
    if(sign(*pC) != 1) {
      printf("Error\n");;
      printOutArithmetic(*pA,*pB,'-');
    }
    //neg - neg < 0
    freeBigInteger(pB);
    freeBigInteger(pC);
    *pB = stringToBigInteger("-110122223333");
    *pC = diff(*pA, *pB);
    if(sign(*pC) != -1){
      printf("Error\n");
      printOutArithmetic(*pA,*pB,'-');
    }

    //neg - pos = neg
    negate(*pB);
    freeBigInteger(pC);
    *pC = diff(*pA, *pB);
    if(sign(*pC) != -1){
      printf("Error 3\n");;
      printOutArithmetic(*pA,*pB,'-');
    }

      *pA = stringToBigInteger("111122223333");
      *pB = stringToBigInteger("111122223333");
			*pC = stringToBigInteger("-111122223333");
			*pD = stringToBigInteger("999111122223333");

			// A = B
			if (!equals(*pA, *pB)) printf("Error 2.1\n");

			// A > C
			if (equals(*pA, *pC)) printf("Error 2.2\n");

            // A < D
      if (equals(*pA, *pD)) printf("Error 2.3\n");

  long i;
  long j;
  long k;
  long start=971541345;
  long end = start+10;
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        testVerb(k,-i,-j,'+');
      }
    }
  }
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        //printf("---> A: %ld B: %ld \n",i,j);
        testVerb(k,j,-i,'-');
      }
    }
  }
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        //printf("---> A: %ld B: %ld \n",i,j);
        testVerb(k,i,-j,'*');
      }
    }
  }
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        testNoun(-i,-j,'+');
      }
    }
  }
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        //printf("---> A: %ld B: %ld \n",i,j);
        testNoun(j,-i,'-');
      }
    }
  }
  for(k=0;k<2;k++){
    for (i=start;i<end;i++){
      for(j=start;j<end;j++){
        //printf("---> A: %ld B: %ld \n",i,j);
        testNoun(i,-j,'*');
      }
    }
  }
  return(0);
}

void printOutArithmetic(BigInteger A, BigInteger B, char* operator){
  BigInteger output = newBigInteger();
  printf("\n------------------------------------------\n");

  printf("  ");
  printBigIntTerm(A);
  if(operator == '+'){
    printf("+");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________-");
    output=sum(A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)+convertBigInt(B));
  }else if(operator == '-'){
    printf("-");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________\n");
    output=diff(A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)-convertBigInt(B));
  }else if (operator == '*'){
    printf("X");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________-");
    output=prod(A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)*convertBigInt(B));
  }
  printf("\n------------------------------------------\n");
  freeBigInteger(&output);
}

void printVerb(BigInteger output, BigInteger A,BigInteger B, char* operator){

  printf("\n------------------------------------------\n");
  printf("  ");
  printBigIntTerm(A);
  if(operator == '+'){
    printf("+");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________\n");
    add(output,A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)+convertBigInt(B));
  }else if(operator == '-'){
    printf("-");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________\n");
    subtract(output,A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)-convertBigInt(B));
  }else if (operator == '*'){
    printf("X");
    printf(" ");
    printBigIntTerm(B);
    printf("__________________________\n");
    multiply(output,A,B);
    printf("  ");
    printBigIntTerm(output);
    printf("\n Expected Output is: %ld \n", convertBigInt (A)*convertBigInt(B));
  }
  printf("\n------------------------------------------\n");
}

void testVerb(long output, long A, long B, char* operator){
    char s1[1000];
    char s2[1000];
    char s3[1000];
    sprintf(s1,"%ld",output);
    sprintf(s2,"%ld",A);
    sprintf(s3,"%ld",B);
    BigInteger AA = stringToBigInteger(s2);
    BigInteger BB = stringToBigInteger(s3);
    BigInteger Out = stringToBigInteger(s1);
    if(operator == '+'){
      add(Out,AA,BB);
      if(convertBigInt(Out) != A+B){
        printVerb(Out,AA,BB,'+');
      }
    }else if(operator == '-'){
      subtract(Out,AA,BB);
      if(convertBigInt(Out) != A-B){
        printVerb(Out,AA,BB,'-');
      }
    }else if (operator == '*'){
      multiply(Out,AA,BB);
      if(convertBigInt(Out) != A*B){
        printVerb(Out,AA,BB,'*');
      }
    }
    freeBigInteger(&AA);
    freeBigInteger(&BB);
    freeBigInteger(&Out);
}

void testNoun(long A, long B, char* operator){
    char s2[1000];
    char s3[1000];
    sprintf(s2,"%ld",A);
    sprintf(s3,"%ld",B);
    BigInteger Out;
    BigInteger AA = stringToBigInteger(s2);
    BigInteger BB = stringToBigInteger(s3);
    if(operator == '+'){
      Out=sum(AA,BB);
      if(convertBigInt(Out) != A+B){
        printOutArithmetic(AA,BB,'+');
      }
    }else if(operator == '-'){
      Out=diff(AA,BB);
      if(convertBigInt(Out) != A-B){
        printOutArithmetic(AA,BB,'-');
      }
    }else if (operator == '*'){
      Out=prod(AA,BB);
      if(convertBigInt(Out) != A*B){
        printOutArithmetic(AA,BB,'*');
      }
    }
    freeBigInteger(&AA);
    freeBigInteger(&BB);
    freeBigInteger(&Out);
}

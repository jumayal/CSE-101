/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA2
* BigInteger.c
* BigInteger ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"
// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.

typedef struct BigIntegerObj{
  List bigInt;
  int sign;
}BigIntegerObj;

BigInteger newBigInteger(){
  BigInteger num = (BigInteger)malloc(sizeof(BigIntegerObj));
  num->bigInt = newList();
  num->sign = 0;
  return(num);
}

void freeBigInteger(BigInteger* pN){
  if (pN!=NULL && *pN!=NULL){
    freeList(&((*pN)->bigInt));
    free(*pN);
    *pN=NULL;
  }
}
int compareNumber(List A, List B, int sign_A,int sign_B);
// Access functions -----------------------------------------------------------
long power(long a, long b);
int sign(BigInteger N){
  return(N->sign);
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
  List ls_A = A->bigInt;
  List ls_B = B->bigInt;
  if(A->sign==0 && B->sign==0){
    return (0);
  }else if(A->sign>B->sign){
    return(1);
  }else if (A->sign < B->sign){
    return(-1);
  }else if (length(ls_A)>length(ls_B)){
    return (1);
  }else if (length(ls_A)<length(ls_B)){
    return (-1);
  }
  moveBack(ls_A);
  moveBack(ls_B);
  return(compareNumber(ls_A,ls_B,A->sign,B->sign));
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
  int lean;
  int comp = compare(A,B);
  if(comp==0){
    lean=1;
  }else{
    lean=0;
  }

  return (lean);
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
  N->sign=0;
  clear(N->bigInt);
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
  N->sign=N->sign*-1;
}
// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
  BigInteger num = newBigInteger();
  List ls = num->bigInt;
  int length =strlen(s);
  int signChar =0;
  long sum=0;
  if(s[0] == '+'){
    num->sign= 1;
    signChar=1;
  }else if (s[0] == '-'){
    num->sign = -1;
    signChar=1;
  }else{
    num->sign =1;
  }
  int i=0;
  int j;
  if( s[length-1] == '\n'){
    i++;
  }
  while(i<length-signChar){
    for(j=0;j<POWER;j++){
      if(i==length-signChar){
        break;
      }
      sum = (s[length-1-i]-48)*power(10,j) + sum;
      i++;
    }
    append(ls,sum);
    sum=0;
  }
  return num;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
  BigInteger copy = newBigInteger();
  freeList(&(copy->bigInt));
  copy->bigInt = copyList(N->bigInt);
  copy->sign = N->sign;
  return copy;
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
  long holder;
  int carry = 0;
  int sign;
  int subtractor ; //1 is A  -1 is B 0 is none
  List sum = newList();
  List AA = copyList(A->bigInt);
  List BB = copyList(B->bigInt);
  moveFront(AA);
  moveFront(BB);
  if(A->sign < B->sign){
    subtractor=1;
  }else if(A->sign > B->sign){
    subtractor =-1;
  }else{
    sign=A->sign;
    subtractor = 0;
  }
  //printf("Boolean %d\n", compareNumber(AA,BB));
  if(subtractor==0){
    moveFront(AA);
    moveFront(BB);
    while(index(AA) >-1 && index(BB) >-1){
      //printf("AA: %ld and BB: %ld ", get(AA),get(BB));
      holder= (A->sign)*get(AA) + (B->sign)*get(BB) +carry;
      carry = holder/BASE;
      append(sum,abs(holder%BASE));
      moveNext(AA);
      moveNext(BB);
    }
    if(abs(carry)>0){
      append(sum,abs(carry));
    }
  }else{
    switch(compareNumber(AA,BB,1,1)){
      case 1:
        moveFront(AA);
        moveFront(BB);
        sign=A->sign;
        while(index(AA) >-1 && index(BB) >-1){
          //("AA: %ld and BB: %ld ", get(AA),get(BB));
          if(get(AA)+carry>= get(BB)){
            holder= (A->sign)*get(AA) + (B->sign)*get(BB) +carry;
            carry=0;
          }else{
            holder= (A->sign)*get(AA) + (B->sign)*get(BB) - subtractor*BASE+ carry;
            carry=subtractor;
          }
          //printf("Sum: %ld Carry: %d\n",holder, carry);
          append(sum,abs(holder));
          moveNext(AA);
          moveNext(BB);
        }
        break;
      case -1:
        moveFront(AA);
        moveFront(BB);
        sign=B->sign;
        while(index(AA) >-1 && index(BB) >-1){
          //printf("AA: %ld and BB: %ld\n", get(AA),get(BB));
          if(get(AA)+carry<= get(BB)){
          //  printf("I am here\n");
            holder= (A->sign)*get(AA) + (B->sign)*get(BB) +carry;
            carry=0;
          }else{
          //  printf("You should be in here");
            holder= (A->sign)*get(AA) + (B->sign)*get(BB) + subtractor*BASE + carry;
            carry=-1*subtractor;
          }
          append(sum,abs(holder));
          moveNext(AA);
          moveNext(BB);
        }
        break;
      case 0:
        if(A->sign != B->sign){
          makeZero(S);
          freeList(&AA);
          freeList(&BB);
          freeList(&sum);
          return;
        }
    }
  }

  while(index(AA) >-1){
    append(sum,get(AA)+carry);
    moveNext(AA);
    carry=0;
  }
  while(index(BB) >-1){
    append(sum,get(BB)+carry);
    moveNext(BB);
    carry=0;
  }
  freeList(&S->bigInt);
  freeList(&AA);
  freeList(&BB);
  S->bigInt=sum;
  S->sign = sign;
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
  BigInteger S = newBigInteger();
  //printf("Begin SUM\n");
  add(S,A,B);
  return S;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
  long holder;
  int carry = 0;
  int sign;
  int simple=1;
  int subtractor ; //1 is A  -1 is B 0 is none
  //printf("Integer A sign %d and Integer B sign %d\n",A->sign,B->sign);
  sign=compare(A,B);
  //sprintf("HEre is the sign %d",sign);
  if(sign == 0){
    //printf("Got in here?");
    makeZero(D);
    return;
  }
  List difference = newList();
  List AA = copyList(A->bigInt);
  List BB = copyList(B->bigInt);
  moveFront(AA);
  moveFront(BB);
  if(A->sign < -(B->sign)){
    subtractor=1;
    //printf("I am in here\n");
  }else if(A->sign > -(B->sign)){
    subtractor =-1;
  }else{
    simple =0;
    sign=A->sign;
  }
  //printf("Boolean %d\n", compareNumber(AA,BB));
  if(simple==1){
    switch(compareNumber(AA,BB,1,1)){
      case 1:
        moveFront(AA);
        moveFront(BB);
        while(index(AA) >-1 && index(BB) >-1){
          //printf("AA: %ld and BB: %ld ", get(AA),get(BB));
          if((get(AA)+carry)>= get(BB)){
            holder= (A->sign)*get(AA) - (B->sign)*get(BB) +carry;
            carry=0;
          }else{
            holder= (A->sign)*get(AA) - (B->sign)*get(BB) - subtractor*BASE+ carry;
            carry=subtractor;
          }
          //printf("difference left: %ld carry: %d\n",holder,carry);
          append(difference,abs(holder));
          moveNext(AA);
          moveNext(BB);
        }
        break;
      case -1:
      //printf("in here?");
        moveFront(AA);
        moveFront(BB);
        while(index(AA) >-1 && index(BB) >-1){
          //printf("AA: %ld and BB: %ld ", get(AA),get(BB));
          if(get(AA)+carry<= get(BB)){
          //  printf("I am here\n");
            holder= (A->sign)*get(AA) - (B->sign)*get(BB) +carry;
            carry=0;
          }else{
          //  printf("You should be in here");
            holder= (A->sign)*get(AA) - (B->sign)*get(BB) + subtractor*BASE + carry;
            carry=-1*subtractor;
          }
          //printf("difference left: %ld\n",holder);
          append(difference,abs(holder));
          moveNext(AA);
          moveNext(BB);
        }
        break;
    }
  }else{
    moveFront(AA);
    moveFront(BB);
    while(index(AA) >-1 && index(BB) >-1){
      //printf("%dAA: %ld and %dBB: %ld ",A->sign, get(AA),B->sign,get(BB));
      holder= (A->sign)*get(AA) - (B->sign)*get(BB) +carry;
      carry = holder/BASE;
      append(difference,abs(holder%BASE));
      //printf("difference left: %ld carry: %d\n",holder,carry);
      moveNext(AA);
      moveNext(BB);
    }
    if(abs(carry)>0){
      append(difference,abs(carry));
    }
  }
  while(index(AA) >-1){
    //printf("AA: %ld Index:%d\n", get(AA),index(AA));
    append(difference,get(AA)+carry);
    moveNext(AA);
    carry=0;
  }
  while(index(BB) >-1){
    //printf("Append");
    append(difference,get(BB)+carry);
    moveNext(BB);
    carry=0;
  }
  //printf("Helll 8%d\n",sign);
  freeList(&D->bigInt);
  freeList(&AA);
  freeList(&BB);
  D->bigInt=difference;
  D->sign = sign;
  //printf("D Sign: %d\n", D->sign);
}
// diff()
// Returns a reference to a new BigInteger object representing A - B
BigInteger diff(BigInteger A, BigInteger B){
  BigInteger D= newBigInteger();
  subtract(D,A,B);
  return D;
}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
  List mult = newList();
  List AA = A->bigInt;
  List BB = copyList(B->bigInt);
  int carry=0;
  int deciPlace;
  long holder;
  int AA_length=length(A->bigInt);
  int BB_length=length(B->bigInt);
  int i;
  if(A->sign *B->sign ==0){
    makeZero(P);
    return;
  }
  deciPlace=length(AA)+length(BB);
  for(i=0;i<deciPlace;i++){
    append(mult,0);
  }
  int j=0;
  int k=0;
  moveFront(BB);
  moveFront(mult);
  deciPlace=0;
  //printf("Front index of mult%d\n", index(mult));
  while(j<BB_length){
    moveFront(AA);
    deciPlace++;
    while(k<AA_length){
      //printf("%ld + product add : %ld and carry :%ld in Index: %d --> %ld\n", get(mult), (get(AA)*get(BB))+carry , (get(mult)+ (get(AA)*get(BB))+carry)/BASE , index(mult), (get(mult)+ (get(AA)*get(BB))+carry)%BASE );
      holder = get(mult)+ (get(AA)*get(BB))+carry;
      set(mult,(holder)%BASE);
      carry = (holder)/BASE;
      moveNext(AA);
      moveNext(mult);
      k++;
    }
    k=0;
    if(carry>0){
      //printf("Adding Carry of %d into index: %d alreadying holding %ld\n", carry, index(mult), get(mult));
      set(mult,(get(mult)+carry));
      carry=0;
    }
    //printf("Index: %d matches %d",index(mult), deciPlace);
    if(deciPlace <1000){
      moveFront(mult);
      while(index(mult)<deciPlace){
        //printf("Index: %d matches %d\n",index(mult), deciPlace);
        moveNext(mult);
      }
    }else{
      while(index(mult)>deciPlace){
        movePrev(mult);
      }
    }
    j++;
    moveNext(BB);
  }
  freeList(&BB);
  P->sign=(A->sign)*(B->sign);
  freeList(&P->bigInt);
  P->bigInt= mult;
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    BigInteger P = newBigInteger();
    multiply(P,A, B);
    return P;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
  List L = N->bigInt;
  char s[32];
  if(N->sign==-1){
    fprintf(out,"-");
  }else if(N->sign == 0){
    fprintf(out,"0");
    //fprintf(out,"\n\n");
    return;
  }
  moveBack(L);
  while(get(L) ==0){
    movePrev(L);
  }
  sprintf(s,"%li",get(L));
   int i=0;
   while(s[i] != '\0'){
    fprintf(out,"%c",s[i]);
      i++;
  }
  int leadingZ;
  for(movePrev(L);index(L)>=0;movePrev(L)){
    sprintf(s,"%li",get(L));
    leadingZ=POWER - strlen(s);
    i=0;
    while(i<leadingZ){
      fprintf(out,"0");
      i++;
    }
    i=0;
    while(s[i] != '\0'){
      fprintf(out,"%c",s[i]);
      i++;
    }
    //fprintf(out,"%.5li",get(L));
  }
}

void printBigIntTerm(BigInteger N){
  List L = N->bigInt;
  for(moveBack(L);index(L)>=0;movePrev(L)){
    printf("%.2li",get(L));
  }
  if(N->sign==1){
    printf("+");
  }else if(N->sign==-1){
    printf("-");
  }
  printf("\n");
}

long power(long a, long b){
  long output =1;
  while(b !=0){
    output *= a;
    b--;
  }
  return output;
}

int compareNumber(List A, List B,int sign_A,int sign_B){
  if(length(A)>length(B)){
    return 1;
  }else if(length(B)>length(A)){
    return -1;
  }
  moveBack(B);
  for(moveBack(A);index(A)>-1;movePrev(A)){
    //printf("Compare A:%ld and B %ld\n",get(A),get(B));
    if((sign_A*get(A))>((sign_B)*get(B))){
      return 1;
    }else if(sign_A*get(A) < sign_B*get(B)){
      return -1;
    }
    movePrev(B);
  }
  return 0;
}
long convertBigInt (BigInteger A){
  List AA = A->bigInt;
  long num=0;
  int i=0;
  for(moveFront(AA);index(AA)>-1;moveNext(AA)){
      num = get(AA)*power(BASE,i) + num;
      i++;
  }
  return num * A->sign;
}

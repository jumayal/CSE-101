/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA6
* DictionaryTest.c
* Tests Dictionary ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"
#define MAX_LEN 160


int main(int argc, char const *argv[]) {
  Dictionary A = newDictionary(1);
  int *enter= (int *)calloc(10,sizeof(int));
  for(int i=1;i<10;i++){
    enter[i]=i;
  }

  insert(A,"Hello",&enter[0]);
  insert(A,"Bye",&enter[1]);
  insert(A,"WhatsUp",&enter[2]);
  insert(A,"ComeOn",&enter[3]);
  insert(A,"Ayo",&enter[4]);
  insert(A,"Dayo",&enter[6]);
  insert(A,"iaddy",&enter[7]);
  insert(A,"zaddy",&enter[8]);
  printDictionary(stdout,A,"pre");
  printDictionary(stdout,A,"in");
  int length = size(A);
  if(length != 8){
    printf("Size is not working in this case\n");
  }

  int uni= getUnique(A);
  if(uni != 1){
    printf("getUnique not working in this case\n");
  }

  VAL_TYPE lu = lookup(A,"Dayo");
  if(*lu != 6){
    printf("lookup is not working in this case\n");
  }

  delete(A,"Bye");
  lu = lookup(A,"Bye");
  if(lu !=VAL_UNDEF){
   printf("delete is not working in this case\n");
  }
  printDictionary(stdout,A,"in");
   makeEmpty(A);
  // printDictionary(stdout,A);
  printDictionary(stdout,A,"in");
  lu = lookup(A,"ComeOn");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  // lu = lookup(A,"Hello");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  //
  insert(A,"Zoinks",&enter[0]);
  insert(A,"Bye",&enter[1]);
  insert(A,"WhatsUp",&enter[2]);
  insert(A,"ComeOn",&enter[3]);
  insert(A,"Ayo",&enter[4]);
  insert(A,"Dayo",&enter[5]);
  insert(A,"Wow",&enter[6]);
  insert(A,"Pow",&enter[7]);
  insert(A,"Farm",&enter[8]);
  insert(A,"Cow",&enter[9]);

  printf("\n");
  //printDictionary(stdout,A);
  printDictionary(stdout,A,"in");
  printDictionary(stdout,A,"pre");
  printDictionary(stdout,A,"post");
  beginForward(A);
  if(strcmp (currentKey(A),"Ayo") != 0){
    printf("beginForward is not working in this case \n");
  }
  next(A);
  next(A);
  next(A);
  if(strcmp (currentKey(A),"Cow") != 0){
    printf("Next is not working in this case \n");
  }
  next(A);
  prev(A);
  next(A);
  next(A);
  next(A);
  prev(A);
  if(strcmp (currentKey(A),"Farm") != 0){
    printf("Prev is not working in this case \n");
  }


  beginReverse(A);
  if(strcmp (currentKey(A),"Zoinks") !=0){
    printf("beginForward is not working in this case \n");
  }
  prev(A);
  prev(A);
  prev(A);
  if(strcmp (currentKey(A),"Pow") != 0){
    printf("Pow beginForward is not working in this case \n");
  }
  prev(A);
  next(A);
  prev(A);
  prev(A);
  prev(A);
  prev(A);
  if(strcmp (currentKey(A),"ComeOn") != 0){
    printf("beginForward is not working in this case \n");
  }
  lu = lookup(A,"Whatsup");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  //
   insert(A,"Zoinks",&enter[0]);
  insert(A,"Bye",&enter[1]);
  insert(A,"WhatsUp",&enter[2]);
  insert(A,"ComeOn",&enter[3]);
  insert(A,"Ayo",&enter[4]);
  insert(A,"Dayo",&enter[5]);
  insert(A,"Wow",&enter[6]);
  insert(A,"Pow",&enter[7]);
  insert(A,"Farm",&enter[8]);
  insert(A,"Cow",&enter[9]);

  printf("\n");
  //printDictionary(stdout,A);
  printDictionary(stdout,A,"in");
  printDictionary(stdout,A,"pre");
  printDictionary(stdout,A,"post");
  beginForward(A);
  if(strcmp (currentKey(A),"Ayo") != 0){
    printf("beginForward is not working in this case \n");
  }
  next(A);
  next(A);
  next(A);
  if(strcmp (currentKey(A),"Cow") != 0){
    printf("Next is not working in this case \n");
  }
  next(A);
  prev(A);
  next(A);
  next(A);
  next(A);
  prev(A);
  if(strcmp (currentKey(A),"Farm") != 0){
    printf("Prev is not working in this case \n");
  }


  beginReverse(A);
  if(strcmp (currentKey(A),"Zoinks") !=0){
    printf("beginForward is not working in this case \n");
  }
  prev(A);
  prev(A);
  prev(A);
  if(strcmp (currentKey(A),"Pow") != 0){
    printf("Pow beginForward is not working in this case \n");
  }
  prev(A);
  next(A);
  prev(A);
  prev(A);
  prev(A);
  prev(A);
  if(strcmp (currentKey(A),"ComeOn") != 0){
    printf("beginForward is not working in this case \n");
  }
  //
  freeDictionary(&A);
  free(enter);
  return 0;
}

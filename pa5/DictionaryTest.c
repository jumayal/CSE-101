/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA1
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
  insert(A,"Hello",1);
  insert(A,"Bye",2);
  insert(A,"WhatsUp",3);
  insert(A,"ComeOn",4);
  insert(A,"Ayo",5);
  insert(A,"Dayo",6);
  insert(A,"iaddy",7);
  insert(A,"zaddy",8);

  int length = size(A);
  if(length != 8){
    printf("Size is not working in this case\n");
  }

  int uni= getUnique(A);
  if(uni != 1){
    printf("getUnique not working in this case\n");
  }

  int lu = lookup(A,"Dayo");
  if(lu != 6){
    printf("lookup is not working in this case\n");
  }

  delete(A,"Bye");
  lu = lookup(A,"Bye");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  printDictionary(stdout,A);

  makeEmpty(A);
  printDictionary(stdout,A);
  lu = lookup(A,"ComeOn");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  lu = lookup(A,"Hello");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }
  lu = lookup(A,"Whatsup");
  if(lu !=VAL_UNDEF){
    printf("delete is not working in this case\n");
  }

  insert(A,"Bye",2);
  insert(A,"WhatsUp",3);
  insert(A,"ComeOn",4);
  insert(A,"Ayo",5);
  insert(A,"Dayo",6);
  insert(A,"Wow",7);
  insert(A,"Pow",8);
  insert(A,"Farm",9);
  insert(A,"Cow",10);
  insert(A,"Zoinks",11);

  printf("\n");
  printDictionary(stdout,A);
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



  freeDictionary(&A);
  return 0;
}

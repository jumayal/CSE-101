/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA1
* Lex.c
* Orders Words within a file Lexological
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 160

int compareTo(char*, char*);

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

  List sortedIndex= newList();  //Create list for sorted Indexes

  /* Reads text from file and places each
   *string a two dimensional array*/
  fseek(in, 0, SEEK_SET);       //File reading cursor at the start of the file
  char text [count][MAX_LEN];   //Initializing text array to hold words from file
  int q=0;                      //q holds the index value to place the word
  while( fgets(line, MAX_LEN, in) != NULL)  {
    strcat(line,"\0");
    strcpy(text[q],line);
     q++;
  }

  int idx=0;
  prepend(sortedIndex,idx);
  for(idx=1; idx<count;idx++){
    for(moveFront(sortedIndex);index(sortedIndex)>=0;moveNext(sortedIndex)){ //Go throuhg list till out of index
      if(strcmp(&text[idx][0],&text[get(sortedIndex)][0])<0){ //If word in array is before word referenced by index
        insertBefore(sortedIndex,idx); //Inserts index of word infront of compared index
        break;
      }
    }
    //Reaches here if the word isn't before those already referenced in the list
    if(index(sortedIndex)<0){ //Word is the last in lex order
      append(sortedIndex,idx);
    }
  }

  //Prints out words in order from list of indexes
  for(moveFront(sortedIndex);index(sortedIndex)>=0;moveNext(sortedIndex)){
    fprintf(out, "%s", text[get(sortedIndex)]);
  }

  freeList(&sortedIndex);
  /* close files */
  fclose(in);
  fclose(out);
  return 0;
  }

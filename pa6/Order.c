/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA5
* Lex.c
* Orders Words within a file Lexological
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"
#define MAX_LEN 160


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

  /* Reads text from file and places each
   *string a two dimensional array*/
  fseek(in, 0, SEEK_SET);       //File reading cursor at the start of the file
  //char text [count][MAX_LEN];   //Initializing text array to hold words from file

  char **text = (char**)malloc (sizeof(char *)*count);
  for(int i=0;i<count;i++){
    text[i]=(char *)malloc(sizeof(char)*MAX_LEN);
  }
  int q=0;                      //q holds the index value to place the word
  while( fgets(line, MAX_LEN, in) != NULL)  {
    strcat(line,"\0");
    strcpy(text[q],line);
     q++;
  }
  Dictionary book = newDictionary(0);
  for(int i=0; i<count;i++){
    insert(book,&text[i][0],NULL);
  }
  fprintf(out,"******************************************************\n");
  fprintf(out,"PRE-ORDER:\n");
  fprintf(out,"******************************************************\n");
  printDictionary(out,book,"pre");
  fprintf(out,"\n******************************************************\n");
  fprintf(out,"IN-ORDER:\n");
  fprintf(out,"******************************************************\n");
  printDictionary(out,book,"in");
  fprintf(out,"\n******************************************************\n");
  fprintf(out,"POST-ORDER:\n");
  fprintf(out,"******************************************************\n");
  printDictionary(out,book,"post");
  freeDictionary(&book);
  for(int i=0;i<count;i++){
    free(text[i]);
  }
  free(text);
  /* close files */
  fclose(in);
  fclose(out);
  return 0;
  }

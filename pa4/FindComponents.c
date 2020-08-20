/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA3
* Graph.h
* Graph header ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
int main(int argc, char const *argv[]) {
  int order;
  int *u=(int*)malloc(sizeof(int));
  int *v =(int*)malloc(sizeof(int));
  FILE *in, *out;
  // check command line for correct number of arguments
  if( argc != 3 ){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if( in==NULL ){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if( out==NULL ){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  fscanf(in,"%d", &order);
  Graph G= newGraph(order);
  fscanf(in,"%d %d", u, v);
  while(*u!=0 && *v!=0){
    addArc(G,*u,*v);
    fscanf(in,"%d %d", u ,v);
  }
  fprintf(out,"Adjacency list representation of G: \n");
  printGraph(out,G);
  List S=newList();
  for(int i=1;i<=order;i++){
    append(S,i);
  }
  DFS(G,S);
  Graph trans=transpose(G);
  DFS(trans,S);

  int *amountCom=(int*)malloc(sizeof(int));
  *amountCom=0;
  for(int j=1;j<=order;j++){
    if(getParent(trans,j)==NIL){
      *amountCom=*amountCom+1;
    }
  }
  fprintf(out,"\nG contains %d strongly connected components:",*amountCom);
  *amountCom=1;
  List ordering=newList();
  moveFront(S);
  while(index(S)>=0){
    if(getParent(trans,get(S))==NIL){
      prepend(ordering,get(S));
      moveNext(S);
      moveFront(ordering);
      while(getParent(trans,get(S))!=NIL && index(S)>=0 && index(ordering)>=0){
        insertAfter(ordering,get(S));
        moveNext(ordering);
        moveNext(S);
      }
    }
  }

  for(moveFront(ordering);index(ordering)>=0;moveNext(ordering)){
    if(getParent(trans,get(ordering))==NIL){
      fprintf(out,"\nComponent %d: ",*amountCom);
      *amountCom=*amountCom+1;
    }
    fprintf(out,"%d ",get(ordering));
  }


  free(amountCom);
  freeList(&S);
  freeGraph(&G);
  freeGraph(&trans);
}

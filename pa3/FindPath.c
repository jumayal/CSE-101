/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA3
* FindPath.c
* Finds the fastest route
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
int main(int argc, char const *argv[]) {
  FILE *in, *out;
  int order;
  int u;
  int v ;
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
  fscanf(in,"%d %d", &u, &v);
  while(u!=0 && v!=0){
    addEdge(G,u,v);
    fscanf(in,"%d %d", &u ,&v);
  }
  printGraph(out,G);
  fprintf(out,"\n");
  fscanf(in,"%d %d", &u, &v);
  List path;
  while(u!=0 && v!=0){
    path=newList();
    BFS(G,u);
    getPath(path,G,v);
    fprintf(out, "%s %d %s %d %s","The distance from", u,"to",v, "is " );
    if(getDist(G,v)<0){
      fprintf(out, "%s", "infinity \n");
    }else{
      fprintf(out, "%d" "%s", getDist(G,v), "\n");
    }
    moveFront(path);
    if(get(path)<=0){
      fprintf(out,"%s %d%s%d %s", "No",u,"-",v,"path exists \n\n");
    }else{
      fprintf(out, "%s %d%s%d %s", "A shortest", u, "-",v,"path is: ");
      printList(out, path);
      fprintf(out,"\n");
    }
    fscanf(in,"%d %d", &u ,&v);
    freeList(&path);
  }
  freeGraph(&G);
  fclose(in);
  fclose(out);
  return 0;
}

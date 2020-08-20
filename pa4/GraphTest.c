/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA4
* GraphTest.c
* Graph Test Client
*********************************************************************************/
#include <stdio.h>
#include "Graph.h"
#include "List.h"

void printL(List L){
  printf("\nList: \n");
  for(moveFront(L);index(L)>=0;moveNext(L)){
    printf(" %d ", get(L));
  }
  printf("\n");
}
int main(void) {
  Graph A = newGraph(100);
List L = newList();
    for (int i = 1; i <= 100; i++){
        if (getFinish(A, i) != UNDEF){
          printf("\n%d should be %d\n",getFinish(A, i),UNDEF);

        }
      }
      addEdge(A, 64, 4);
      addEdge(A, 64, 3);
      addEdge(A, 42, 2);
      addEdge(A, 2, 64);
      addEdge(A, 4, 2);
      addEdge(A, 3, 42);
      for (int i = 1; i <= 100; i++) {
        prepend(L, i);
      }
      DFS(A, L);
      printf("\n\n*************************************************\n\n");

      if (getFinish(A, 100) != 2){
        printf("\nVertex %d:%d should be %d\n",100,getFinish(A, 100),2);

      }
      if (getFinish(A, 64) != 82){
          printf("\nVertex %d:%d should be %d\n",64,getFinish(A, 64),82);
      }
      if (getFinish(A, 42) != 80){
          printf("\nVertex %d:%d should be %d\n",42,getFinish(A, 42),80);
      }
      printf("\n\n*************************************************\n\n");
      DFS(A, L);
      printf("\n\n*************************************************\n\n");
      if (getFinish(A, 64) != 128){
          printf("\nVertex %d:%d should be %d\n",64,getFinish(A, 64),128);
      }
      if (getFinish(A, 63) != 118){
          printf("\nVertex %d:%d should be %d\n",63,getFinish(A, 63),118);
      }
      printf("\n\n*************************************************\n\n");

      DFS(A, L);
      printf("\n\n*************************************************\n\n");

      if (getFinish(A, 65) != 72){
          printf("\nVertex %d:%d should be %d\n",65,getFinish(A, 65),72);
      }
      if (getFinish(A, 1) != 200){
          printf("\nVertex %d:%d should be %d\n",1,getFinish(A, 1),200);
      }
      printf("\n\n*************************************************\n\n");

      return 0;
    printf("\nOMG you finally made it\n");
 }

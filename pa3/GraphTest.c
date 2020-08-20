/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA3
* GraphTest.c
* Tests the functions of Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"
 int main(int argc, char const *argv[]) {
    FILE  *out;
    if( argc != 2 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }
    out = fopen(argv[1], "w");
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    Graph A = newGraph(100);
    List L = newList();
    List C= newList();

    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addArc(A, 3, 42);
    printGraph(out,A);
    BFS(A, 4);
    getPath(L, A, 3);
    append(C, 3);
    append(C, 64);

    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    append(C, 2);
    if (!equals(L, C)){
      printf("L and C should equal\n");

    }
    getPath(L, A, 99);
    if (equals(L, C)){
      printf("L and C shouldNT equal\n");
    }

    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C, L)){
      printf("L and C should equal\n");
    }
    printGraph(out,A);
    freeList(&L);
    freeList(&C);
    freeGraph(&A);
    fclose(out);
    printf("\nYou finally made it\n");
    return 0;
 }

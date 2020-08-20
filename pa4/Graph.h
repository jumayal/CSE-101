/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA4
* Graph.h
* Graph ADT header file
*********************************************************************************/
#ifndef _STACK_H_INCLUDE_
#define _STACK_H_INCLUDE_
#include"List.h"
#define NIL -1
#define UNDEF -8
/***Exported type***/
typedef struct GraphObj *Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
 int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
#endif

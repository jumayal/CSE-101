/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA3
* Graph.h
* Graph header ADT
*********************************************************************************/
#ifndef _STACK_H_INCLUDE_
#define _STACK_H_INCLUDE_
#include "List.h"
#define NIL -1
#define INF -8
/***Exported type***/
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
List* getList(Graph g);
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
#endif

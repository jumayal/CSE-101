/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA3
* Graph.c
* Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
// #define NIL -1
// #define INF -8
/***Exported type***/
typedef struct GraphObj{
  List *adjList; //an array of list pointers. Each list containing the connected nodes to one index
  char *discover; //an array of one character signifying colors white(w), gray(g), black(b) for vertix i
  int *parent; //an array of the vertx that is the parent to vertex i
  int *distance; // the distance from the source of vertex i
  int *order; //number of vertices
  int *size; //number of edges
  int *sV; //Recent source vertex
}GraphObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
  Graph graph=(Graph)(malloc(sizeof(GraphObj)));
  graph->adjList= (List*)(malloc(sizeof(List)*(n+1)));
  graph->discover=(char*)(malloc(sizeof(char)*(n+1)));
  graph->parent =(int*)(malloc(sizeof(int)*(n+1)));
  graph->distance=(int*)(malloc(sizeof(int)*(n+1)));
  graph->order=(int*)(malloc(sizeof(int)));
  graph->size=(int*)(malloc(sizeof(int)));
  graph->sV=(int*)(malloc(sizeof(int)));
  *(graph->order)=n;
  *(graph->size)=0;
  *(graph->sV)=NIL;
  int i;
  for (i=0;i<n+1;i++){
    graph->adjList[i]=NULL;
  }
  return (graph);
}

List* getList(Graph g){
  return g->adjList;
}
void freeGraph(Graph* pG){
  if(pG!=NULL && *pG !=NULL){
    for(int i=1;i<=getOrder(*pG);i++){
      freeList(&((*pG)->adjList[i]));
    }
    free((*pG)->adjList);
    free((*pG)->discover);
    free((*pG)->parent);
    free((*pG)->distance);
    free((*pG)->order);
    free((*pG)->size);
    free((*pG)->sV);
    (*pG)->adjList=NULL;
    (*pG)->discover=NULL;
    (*pG)->parent=NULL;
    (*pG)->distance=NULL;
    (*pG)->order=NULL;
    (*pG)->size=NULL;
    (*pG)->sV=NULL;
    free(*pG);
    *pG=NULL;
  }
}
/*** Access functions ***/
int getOrder(Graph G){
  return *(G->order);
}
int getSize(Graph G){
  return *(G->size);
}
int getSource(Graph G){
  if((G->sV)==NULL){
    return (NIL);
  }
  return *(G->sV);
}
int getParent(Graph G, int u){
  if(getSource(G)==NIL){
    return (NIL);
  }
  return G->parent[u];
}
int getDist(Graph G, int u){
  if(getSource(G)==NIL){
    return(INF);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u){
  if(getSource(G)==NIL){ //If graph does not exist
    return;
  }else if( G->adjList[u]==NULL || G->adjList[getSource(G)]==NULL){ //if there is no vertex connection with vertext u OR recent vertex has no connecting nodes ->append
    append(L,NIL);
    return;
  }
  List newPath = newList();
  int vertex=u;
  prepend(newPath,vertex);
  while(vertex != getSource(G) && vertex!=0){
    vertex=getParent(G,vertex);
    prepend(newPath, vertex);
  }
  for(moveFront(newPath); index(newPath)>=0;moveNext(newPath)){
    append(L,get(newPath));
  }
  freeList(&newPath);
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
  int order= getOrder(G);
  freeGraph(&G);
  G=newGraph(order);
}
void addEdge(Graph G, int u, int v){
  List v1=G->adjList[u];
  if(v1==NULL){
    G->adjList[u]=newList();
    append(G->adjList[u],v);
  }else{
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>v){
        insertBefore(v1,v);
        break;
      }
    }
    if(index(v1)<0){
      append(v1,v);
    }
  }

  v1=G->adjList[v];
  if(v1==NULL){
    G->adjList[v]=newList();
    append(G->adjList[v],u);
  }else{
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>u){
        insertBefore(v1,u);
        break;
      }
    }
    if(index(v1)<0){
      append(v1,u);
    }
  }
  *(G->size)=*(G->size)+1;
}
void addArc(Graph G, int u, int v){
  if(G->adjList[u]==NULL){
    G->adjList[u]=newList();
    append(G->adjList[u],v);
  }else{
    List v1=G->adjList[u];
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>v){
        insertBefore(v1,v);
        break;
      }
    }
    if(index(v1)<0){
      append(v1,v);
    }
  }
  *(G->size)=*(G->size)+1;
}
void BFS(Graph G, int s){
  char *clrArray=G->discover;
  int * distArray=G->distance;
  int * parArray= G->parent;
  List * edgeArray=G->adjList;
  *(G->sV)=s;
  for(int i=1;i<=getOrder(G);i++){
    clrArray[i] = 'w';
    distArray[i]=INF;
    parArray[i]=NIL;
  }
  clrArray[s]= 'g';
  distArray[s]=0;
  parArray[s]=NIL;
  if(edgeArray[s]==NULL){
    return;
  }
  List Q=newList();
  List vertex;
  int u;
  int v;
  append(Q,s);
  while(length(Q) != 0){
    moveFront(Q);
    u=get(Q);
    deleteFront(Q);
    vertex= edgeArray[u];
    for(moveFront(vertex); index(vertex)>=0;moveNext(vertex)){
      v=get(vertex);
      if(clrArray[v]== 'w'){
        clrArray[v] = 'g';
        distArray[v]=distArray[u]+1;
        parArray[v]=u;
        append(Q,v);
      }
    }
    clrArray[u]='b';
  }
  freeList(&Q);
}
void printGraph(FILE* out, Graph G){
  List *ajLst= G->adjList;
  List holder;
  for(int i=1; i<=getOrder(G);i++){
    holder=ajLst[i];
    fprintf(out,"%d" "%s", i,": ");
    if(holder!=NULL){
      printList(out,holder);
    }else{
      fprintf(out,"%s", "\n");
    }
  }


}

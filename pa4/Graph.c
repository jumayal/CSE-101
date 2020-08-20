/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA4
* Graph.c
* Graph ADT file
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

/***Exported type***/
typedef struct GraphObj{
  List *adjList; //an array of list pointers
  char *color; //an arryay of one character signifying colors white(w), gray(g), black(b) for vertix i
  int *discover; //when the vertex is discoverd
  int *parent; //an array of the vertx that is the parent to vertex i
  int *finish;
  int *order; //number of vertices
  int *size; //number of edges
  int *sV; //Recent source vertex
}GraphObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
  Graph graph;
  graph=(GraphObj*)(malloc(sizeof(GraphObj)));
  graph->adjList= (List*)(malloc(sizeof(List)*(n+1)));
  graph->color=(char*)(malloc(sizeof(char)*(n+1)));
  graph->parent =(int*)(malloc(sizeof(int)*(n+1)));
  graph->finish =(int*)(malloc(sizeof(int)*(n+1)));
  graph->discover =(int*)(malloc(sizeof(int)*(n+1)));
  graph->order=(int*)(malloc(sizeof(int)));
  graph->size=(int*)(malloc(sizeof(int)));
  graph->sV=(int*)(malloc(sizeof(int)));
  *(graph->order)=n;
  *(graph->size)=0;
  *(graph->sV)=NIL;
  for(int i=1; i<=n;i++){
    graph->finish[i]=UNDEF;
    graph->discover[i]=UNDEF;
    graph->adjList[i]=NULL;
  }
  return (graph);
}

List getList(Graph G, int u){
 return G->adjList[u];
}
void freeGraph(Graph* pG){
  if(pG!=NULL && *pG !=NULL){
    for(int i=1;i<=getOrder(*pG);i++){
      freeList(&((*pG)->adjList[i]));
    }
    free((*pG)->adjList);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->finish);
    free((*pG)->discover);
    free((*pG)->order);
    free((*pG)->size);
    free((*pG)->sV);
    (*pG)->adjList=NULL;
    (*pG)->color=NULL;
    (*pG)->parent=NULL;
    (*pG)->finish=NULL;
    (*pG)->discover=NULL;
    (*pG)->order=NULL;
    (*pG)->size=NULL;
    (*pG)->sV=NULL;
    free(*pG);
    pG=NULL;
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
int getDiscover(Graph G, int u){
  return G->discover[u];
}
int getFinish(Graph G,int u){
  return G->finish[u];
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
  int *holder=(int*)malloc(sizeof(int));
  *holder= getOrder(G);
  freeGraph(&G);
  G=newGraph(*holder);
  free(holder);
  holder=NULL;
}
void addEdge(Graph G, int u, int v){
  List v1=G->adjList[u];
  int *repeat = (int*)malloc(sizeof(int));
  if(v1==NULL){
    G->adjList[u]=newList();
    append(G->adjList[u],v);
  }else{
    *repeat=0;
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>v){
        insertBefore(v1,v);
        break;
      }else if(get(v1)==v){
        *repeat=1;
      }
    }
    if(index(v1)<0 && *repeat==0){
      append(v1,v);
    }
  }

  v1=G->adjList[v];
  if(v1==NULL){
    G->adjList[v]=newList();
    append(G->adjList[v],u);
  }else{
    *repeat=0;
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>u){
        insertBefore(v1,u);
        break;
      }else if(get(v1)==u){
        *repeat=1;
      }
    }
    if(index(v1)<0 && *repeat==0){
      append(v1,u);
    }
  }
  free(repeat);
  repeat=NULL;
  *(G->size)=*(G->size)+1;
  v1=NULL;
}
void addArc(Graph G, int u, int v){
  int *repeat = (int*)malloc(sizeof(int));
  *repeat=0;
  if(G->adjList[u]==NULL){
    G->adjList[u]=newList();
    append(G->adjList[u],v);
  }else{
    List v1=G->adjList[u];
    for(moveFront(v1); index(v1)>=0;moveNext(v1)){
      if(get(v1)>v){
        insertBefore(v1,v);
        break;
      }else if(get(v1)==v){
        *repeat=1;
      }
    }
      if(index(v1)<0 && *repeat==0){
        append(v1,v);
      }
  }
    free(repeat);
    repeat=NULL;
  *(G->size)=*(G->size)+1;
}
void visit(Graph G,int u,List S, int* tme){
  char *clrArray=G->color;
  int *discArray=G->discover;
  int *parArray= G->parent;
  int *finArray=G->finish;
  List *edgeArray=G->adjList;
  *tme=*tme+1;
  *(G->sV)=u;
  discArray[u]= *tme;
  clrArray[u]= 'g';
  List vertex= edgeArray[u];
  if(vertex!=NULL){
    int *v =(int*)malloc(sizeof(int));
    for(moveFront(vertex); index(vertex)>=0;moveNext(vertex)){
      *v=get(vertex);
      if(clrArray[*v]=='w'){
        parArray[*v]=u;
        visit(G,*v,S,tme);
      }
    }
    free(v);
  }
  clrArray[u]='b';
  *tme=*tme+1;
  prepend(S,u);
  finArray[u]=*tme;
}

void DFS(Graph G, List S ){
  char *clrArray=G->color;
  int *parArray= G->parent;
  int *tme=(int*)malloc(sizeof(int));
  List stack=newList();
  for(int i=1;i<=getOrder(G);i++){
    clrArray[i] = 'w';
    parArray[i]=NIL;
  }
  *tme=0;
  for(moveFront(S); index(S)>=0;moveNext(S)){
    if(clrArray[get(S)]=='w'){
      visit(G,get(S),stack,tme);
    }
  }
  clear(S);
  for(moveFront(stack); index(stack)>=0;moveNext(stack)){
    append(S,get(stack));
  }
  free(tme);
  freeList(&stack);
}

Graph transpose(Graph G){
  int *order = (int*)malloc(sizeof(int));
  *order=getOrder(G);
  Graph twin=newGraph(*order);
  List V; //the vertex being looked at
  for(int i=1;i<=*order;i++){
    V=G->adjList[i];
    if(V!=NULL){
      for(moveFront(V);index(V)>=0;moveNext(V)){
        addArc(twin,get(V),i);
      }
    }
  }
  return (twin);
}

Graph copyGraph(Graph G){
  int *order = (int*)malloc(sizeof(int));
  *order=getOrder(G);
  Graph copy=newGraph(*order);
  for(int i=0;i<=*order;i++){
    copy->adjList[i]=copyList(G->adjList[i]);
    copy->color[i]= G->color[i];
    copy->parent[i]=G->parent[i];
    copy->discover[i]=G->discover[i];
  }
  *(copy->order)=*(G->order);
  *(copy->size)=*(G->size);
  *(copy->sV)=*(G->sV);
  free(order);
  order=NULL;
  return (copy);
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

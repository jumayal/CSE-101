/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA1
* List.c
* List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
  ELEMENT_TYPE item;
  struct NodeObj* next;
  struct NodeObj* prev;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct listObj{
  Node head;
  Node tail;
  Node cursor;
  int indx;
  int length;
}listObj;

int ls_compare(Node L, Node first);
// Constructors-Destructors ---------------------------------------------------
Node newNode(ELEMENT_TYPE item){
   Node N =(Node)malloc(sizeof(NodeObj));
   N->item = item;
   N-> next = NULL;
   N->prev=NULL;
   return(N);
}
Node newN(void){
   Node N = (Node)malloc(sizeof(NodeObj));
   N->next = NULL;
   N->prev=NULL;
   return(N);
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
List newList(void){
  List L;
  L= (listObj*)malloc(sizeof(listObj));
  L->head = NULL;
  L->tail = NULL;
  L->cursor=NULL;
  L->length = 0;
  L->indx=-1;
  return(L);
}
void freeList(List* pL){
  if( pL!=NULL && *pL!=NULL){
      moveFront(*pL);
      while(length(*pL)>0){
        deleteBack(*pL);
      }
     free(*pL);
     *pL=NULL;
  }
}

// Access functions -----------------------------------------------------------
int length(List L){
  if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
  return (L->length);
}
int index(List L){
  if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return (L->indx);
}
void putIndex(List L,int i){
  L->indx=i;
}
ELEMENT_TYPE front(List L){
  if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   return ((L->head)->item);
}
ELEMENT_TYPE back(List L){
  if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   return ((L->tail)->item);
}
ELEMENT_TYPE get(List L){
  if(L->length>0 && L->indx>=0){
    return((L->cursor)->item);
  }
  return (-1);
}

int ls_equals(List A, List B){
  if(A->head==NULL && B->head==NULL){
    return(1);
  }else if(A->head==NULL || B->head==NULL){
    return (0);
  }
  return ls_compare(A->head,B->head);
}
// Manipulation procedures ----------------------------------------------------
void clear(List L){
  moveFront(L);
  while(length(L)>0){
    deleteBack(L);
  }
}
void moveFront(List L){
  if(L->length>0){
    L->indx=0;
    L->cursor=L->head;
  }else{
    L->indx=-1;
  }
}
void moveBack(List L){
  if(L->length>0){
    L->indx=(L->length)-1;
    L->cursor=L->tail;
  }else{
    L->indx=-1;
  }
}
void movePrev(List L){
  if((L->cursor) == (L->head)){
    L->indx=-1;
    L->cursor=NULL;
  }else if(L->cursor==NULL){
    return;
  }else{
    L->indx=(L->indx)-1;
    L->cursor=(L->cursor)->prev;
  }
}
void moveNext(List L){
  if(L->cursor == L->tail){
    L->indx=-1;
    L->cursor=NULL;
  }else if(L->cursor!=NULL){
    L->indx=(L->indx)+1;
    L->cursor=(L->cursor)->next;
  }
}
void prepend(List L, ELEMENT_TYPE data){
  L->length=(L->length)+1;
  Node pH=L->head;
  Node item = newNode(data);
  if((L->length)>1){
    item->next=pH;
    pH->prev= item;
    L->head=item;
    if((L->indx)>=0){
     L->indx=(L->indx)+1;
    }
  }else{
    L->head=item;
    L->tail=L->head;
  }
}
void append(List L, ELEMENT_TYPE data){
  L->length=(L->length)+1;
  Node pT= L->tail;
  Node item = newNode(data);
  if(L->length>1){
    pT->next=item;
    item->prev=pT;
    L->tail=item;
  }else{
    L->head=item;
    L->tail=L->head;
  }
}
void insertBefore(List L, ELEMENT_TYPE data){
  if(L->length>0 && L->indx>=0){
    if(L->indx>=1){
      Node item = newNode(data);
      item->prev=(L->cursor)->prev;
      (L->cursor)->prev=item;
      (item->prev)->next=item;
      item->next=L->cursor;
      L->indx=(L->indx)+1;
      L->length=(L->length)+1;
    }else{
      prepend(L,data);
    }
  }
}
void insertAfter(List L, ELEMENT_TYPE data){
  if((L->length)>0 && (L->indx) >=0){
    if(L->indx < (L->length)-1){
      Node item= newNode(data);
      item->next=(L->cursor)->next;
      item->prev=L->cursor;
      (L->cursor)->next->prev=item;
      (L->cursor)->next=item;
      L->length=(L->length)+1;
    }else{
      append(L,data);
    }
  }
}
void deleteFront(List L){
  if(L!=NULL){
    Node temp = L->head;
    if((L->length)>1){
      L->head=(L->head)->next;
      if(L->indx>=0){
        L->indx=(L->indx)-1;
      }
    }else{
      L->head=NULL;
      L->tail=L->head;
      L->indx=-1;
    }
    L->length=(L->length)-1;
    freeNode(&temp);
  }
}
void deleteBack(List L){
  if(L!=NULL){
    Node temp = L->tail;
    if(L->length>1){
      L->tail=(L->tail)->prev;
      L->tail->next=NULL;
      if(L->indx==L->length-1){
        L->indx=-1;
      }
    }else{
      L->head = NULL;
      L->tail= NULL;
      L->indx=-1;
    }
    L->length=L->length-1;
    freeNode(&temp);
  }
}
void delete(List L){
  if(L->length>0 && L->indx>=0){
    if(L->indx == (L->length)-1){
      deleteBack(L);
    }else if(L->indx==0){
      deleteFront(L);
    }else{
      Node temp = L->cursor;
      L->cursor->prev->next=L->cursor->next;
      L->cursor->next->prev=L->cursor->prev;
      freeNode(&temp);
      L->cursor=NULL;
      L->indx=-1;
      L->length=(L->length)-1;
    }
  }
}

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, ELEMENT_TYPE x){
  if(L->length>0 && L->indx>=0){
    L->cursor->item=x;
  }
}
// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){
  int holder=index(L);  //Holds current index so it is not forgoten
  for(moveFront(L);index(L)>=0;moveNext(L)){
    fprintf(out,"%li ",get(L));
  }
  fprintf(out,"\n");
  L->indx=holder;
}

List copyList(List L){
  List twin = newList();
  int holder=index(L); //Holds current index so it is not forgoten
  for(moveFront(L);index(L)>=0; moveNext(L)){
    append(twin,get(L));
  }
  L->indx=holder;
  return twin;
}

int ls_compare(Node L, Node first){
  if(L->next == NULL && first->next==NULL){
    return(1);
  }else if(L->item != first->item || L->next==NULL || first->next==NULL){
    return(0);
  }
  return ls_compare(L->next,first->next);
}

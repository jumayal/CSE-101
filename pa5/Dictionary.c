/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA5
* Dictionary.c
* Dictionary ADT
*********************************************************************************/
#include "Dictionary.h"

typedef struct NodeObj{
  KEY_TYPE key;
  VAL_TYPE value;
  struct NodeObj* parent;
  struct NodeObj* right;
  struct NodeObj* left;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct DictionaryObj{
  Node tree;
  Node cursor;
  int size;
  int unique;
  int dir;
}DictionaryObj;

Node newNode(KEY_TYPE key,VAL_TYPE value){
   Node N =(Node)malloc(sizeof(NodeObj));
   N->value = value;
   N->key = key;
   N->parent=NULL;
   N->right =NULL;
   N->left=NULL;
   return(N);
}

Dictionary newDictionary(int unique){
  Dictionary D = (DictionaryObj*)malloc(sizeof(DictionaryObj));
  D-> cursor=NULL;
  D->size=0;
  D->unique=unique;
  D->tree= NULL;
  D->dir=0;
  return D;
}
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

void freeDictionary (Dictionary* pD){
  if((*pD)->size==0){
    free(*pD);
    *pD=NULL;
    return;
  }
  Node pin = (*pD)->tree;
  Node back;
  while((*pD)->tree->right !=NULL || (*pD)->tree->left !=NULL){
    if(pin->left !=NULL){
      pin=pin->left;
    }else if(pin->right !=NULL){
      pin=pin->right;
    }else{
      back=pin->parent;
      if(back->left ==pin){
        freeNode(&(back->left));
      }else{
        freeNode(&(back->right));
      }
      pin=back;
    }
  }
  freeNode(&((*pD)->tree));
  free(*pD);
  *pD=NULL;
}


int size(Dictionary D){
  return (D->size);
}

int getUnique(Dictionary D){
  return (D->unique);
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
  Node leaf = D->tree;
  int compare =0;
  while(leaf != NULL){
    compare = KEY_CMP(k,leaf->key);
    if(compare ==0){
      return leaf->value;
    }
    if(compare >0){
      leaf = leaf->right;
    }else{
      leaf = leaf->left;
    }
  }
  return VAL_UNDEF;
}

Node treeMinimum(Node x);
Node treeMaximum(Node x);
// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    Node leaf = D->tree;
    Node item = newNode(k,v);
    int compare;
    //printf("I am entering right now\n");
    if(D->size == 0){
      //printf("Putting %s with index %d\n", k,v);
      D->tree=item;
      D->size=D->size+1;
      return;
    }
    //printf("Value:%d\n", (D->tree)->value);
    while(leaf!= NULL){
      compare = KEY_CMP(k,leaf->key);
      if(compare ==0 ){
        if(getUnique(D)){
          return;
        }
      }
      if(compare >=0){
        if(leaf->right == NULL){
          leaf->right=item;
          item->parent=leaf;
          //printf("Putting %s with index %d to the right\n", k,v);
          break;
        }
        leaf = leaf->right;
      }else{
        if(leaf->left ==NULL){
          //printf("Putting %s with index to the left %d\n", k,v);
          leaf->left=item;
          item->parent=leaf;
          break;
        }
        leaf = leaf->left;
      }
    }
    D->size=D->size+1;
}

void transplant( Dictionary D, Node u, Node v){
  if( u->parent == NULL){
    D->tree = v;
  }else if (u == (u->parent)->left){
    u->parent->left = v;
  }else{
    u->parent->right =v;
  }
  if(v !=NULL ){
    v->parent = u->parent;
  }
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
  Node leaf = D->tree;
  int compare = KEY_CMP(k,leaf->key);
  Node holder;
  while(compare !=0){
    if(leaf ==  NULL){
      return;
    }else if(compare >0){
      leaf = leaf->right;
    }else{
      leaf = leaf->left;
    }
    compare = KEY_CMP(k,leaf->key);
  }
  if(D->cursor ==leaf){
    D->cursor=NULL;
  }
  if( leaf ->left == NULL){
    transplant(D, leaf, leaf->right);
  }else if(leaf->right == NULL){
    transplant(D,leaf,leaf->left);
  }else{
    holder = treeMinimum(leaf->right);
    if(holder->parent != leaf){
      transplant(D,holder,holder->right);
      holder->right=leaf->right;
      (holder->right)->parent=holder;
    }
    transplant(D,leaf,holder);
    holder->left=leaf->left;
    holder->left->parent=holder;
  }
  D->size=D->size-1;
  freeNode(&leaf);
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
  if(D->size ==0){
    return;
  }
  Node pin = D->tree;
  D->dir=0;
  Node back;
  while(D->tree->right !=NULL || D->tree->left !=NULL){
    if(pin->left !=NULL){
      pin=pin->left;
    }else if(pin->right !=NULL){
      pin=pin->right;
    }else{
      back=pin->parent;
      if(back->left ==pin){
        freeNode(&(back->left));
      }else{
        freeNode(&(back->right));
      }
      pin=back;
    }
  }
  freeNode(&(D->tree));
  D->size=0;
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D){
  if(D->size ==0){
    return VAL_UNDEF;
  }
  D->dir=1;
  D->cursor = treeMinimum(D->tree);
  return (D->cursor)->value;
}


// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
  if(D->size ==0){
    return VAL_UNDEF;
  }
  D->dir=-1;
  D->cursor = treeMaximum(D->tree);
  return (D->cursor)->value;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
  if(D->dir == 0 || D->cursor ==NULL){
    return KEY_UNDEF;
  }
  return (D->cursor)->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if(D->dir == 0|| D->cursor ==NULL){
      return VAL_UNDEF;
    }
    return (D->cursor)->value;
}


// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
  Node start = D->cursor;
  // printf("------------------------ Start Next Operation ------------------------------------\n");
  // printf("Start Node: %s  %d\n", start->key,start->value);
  // if(start->left == NULL){
  //   printf("Does Not have left Node\n");
  // }else{
  //   printf("Left Node Key: %s\n", start->left->key);
  // }
  // if(start->right == NULL){
  //   printf("Does Not have Right Node\n");
  // }else{
  //   printf("Right Node Key: %s\n", start->right->key);
  // }
  if(D->dir==0 || (start->parent == NULL && start->right ==NULL)){
    D->dir=0;
    return VAL_UNDEF;
  }else if((start->right == NULL) && (start->left == NULL) && (start == (start->parent)->left)){
    D->cursor = start->parent;
    // printf("Case 1: %s  %d\n", D->cursor->key,D->cursor->value);
    // printf("------------------------ End Next Operation ------------------------------------\n");
  }else if (start->right !=NULL){
    start=start->right;
    if(start->left != NULL){
      start=treeMinimum(start);
    }
    D->cursor=start;
    // printf("Case 2: %s %d\n", start->key,start->value);
    // printf("------------------------ End Next Operation ------------------------------------\n");
  }else{
    while(start->parent->right == start){
      start=start->parent;
      if(start->parent == NULL){
        D->dir=0;
        return VAL_UNDEF;
      }
    }
    D->cursor=start->parent;
  }
    // printf("Case 3.3: %s  %d\n", (D->cursor)->key,D->cursor->value);
    // printf("------------------------ End Next Operation ------------------------------------\n");
  return D->cursor->value;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D){
  Node start = D->cursor;
  // printf("------------------------ Start Next Operation ------------------------------------\n");
  // printf("Start Node: %s  %d\n", start->key,start->value);
  // if(start->left == NULL){
  //   printf("Does Not have left Node\n");
  // }else{
  //   printf("Left Node Key: %s\n", start->left->key);
  // }
  // if(start->right == NULL){
  //   printf("Does Not have Right Node\n");
  // }else{
  //   printf("Right Node Key: %s\n", start->right->key);
  // }
  if(D->size==0 || (start->parent == NULL && start->left ==NULL)){
    D->dir=0;
    return VAL_UNDEF;
  }else if((start->right == NULL) && (start->left == NULL) && (start == (start->parent)->right)){
    D->cursor = start->parent;
  // printf("Case 1: %s  %d\n", D->cursor->key,D->cursor->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  }else if (start->left !=NULL){
    start =start->left;
    if(start->right != NULL){
      start=treeMaximum(start);
    }
    D->cursor=start;
  // printf("Case 2: %s %d\n", start->key,start->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  }else{
    while((start->parent)->left == start){
      start=start->parent;
    //printf("Case 3 (Moving Up): %s  %d\n", start->key,start->value);
      if(start->parent == NULL){
        D->dir=0;
        return VAL_UNDEF;
      }
    }
    D->cursor =start->parent;
  }
  // printf("Case 3.3: %s  %d\n", (D->cursor)->key,D->cursor->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  return D->cursor->value;
}


Node treeMinimum(Node x){
  Node leaf =x;
  while (leaf->left != NULL){
    leaf=leaf->left;
  }
  return leaf;
}
Node treeMaximum(Node x){
  Node leaf =x;
//printf("In tree Maximum \n");
  while (leaf->right != NULL){
    leaf=leaf->right;
  //printf("Within Maxtre %s with %d\n", leaf->key,leaf->value);
  }
  return leaf;
}
// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
  if(D->size>0 && D !=NULL){
    VAL_TYPE holder=0;
    holder=beginForward(D);
    while(holder != VAL_UNDEF){
      fprintf(out,KEY_FORMAT,(D->cursor)->key);
      fprintf(out," ");
      fprintf(out,VAL_FORMAT,holder);
      fprintf(out,"\n");
      holder=next(D);
    }
  }
}

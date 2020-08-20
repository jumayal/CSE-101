/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA6
* Dictionary.c
* Dictionary ADT Implimented with Red-black Tree
*********************************************************************************/
#include "Dictionary.h"

typedef struct NodeObj{
  KEY_TYPE key;
  VAL_TYPE value;
  int color; //1 is red 0 is black
  struct NodeObj* parent;
  struct NodeObj* right;
  struct NodeObj* left;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct DictionaryObj{
  Node tree;
  Node cursor;
  Node nil;
  int size;
  int unique;
  int dir;
}DictionaryObj;

Node newNode(KEY_TYPE key,VAL_TYPE value){
   Node N =(Node)malloc(sizeof(NodeObj));
   N->value = value;
   N->key = key;
   N->color=1;
   N->parent=NULL;
   N->right =NULL;
   N->left=NULL;
   return(N);
}

Dictionary newDictionary(int unique){
  int holder =0;
  Dictionary D = (DictionaryObj*)malloc(sizeof(DictionaryObj));
  D->nil=newNode("",&holder);
  D-> cursor=D->nil;
  D->nil->color=0;
  D->size=0;
  D->unique=unique;
  D->tree= D->nil;
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
    freeNode(&((*pD)->nil));
    free(*pD);
    *pD=NULL;
    return;
  }
  Node pin = (*pD)->tree;
  Node back;
  while((*pD)->tree->right !=(*pD)->nil || (*pD)->tree->left !=(*pD)->nil){
    if(pin->left !=(*pD)->nil){
      pin=pin->left;
    }else if(pin->right !=(*pD)->nil){
      pin=pin->right;
    }else{
      back=pin->parent;
      if(back->left ==pin){
        freeNode(&(back->left));
        back->left=(*pD)->nil;
      }else{
        freeNode(&(back->right));
        back->right=(*pD)->nil;
      }
      pin=back;
    }
  }
  freeNode(&((*pD)->tree));
  freeNode(&((*pD)->nil));
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
  while(leaf != D->nil ){
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

Node treeMinimum(Dictionary D, Node x);
Node treeMaximum(Dictionary D, Node x);
// Manipulation procedures ----------------------------------------------------
void Left_Rotate(Dictionary D, Node x){
  Node y = x->right;
  x->right=y->left;
  if(y->left != D->nil ){
    y->left->parent=x;
  }
  y->parent=x->parent;
  if(x->parent == D->nil){
    D->tree=y;
  }else if(x==x->parent->left){
    x->parent->left =y;
  }else{
    x->parent->right=y;
  }
  y->left=x;
  x->parent=y;
}

void Right_Rotate(Dictionary D,Node x){
  Node y = x->left;
  x->left=y->right;
  if(y->right != D->nil){
    y->right->parent=x;
  }
  y->parent=x->parent;
  if(x->parent == D->nil){
    D->tree=y;
  }else if(x==x->parent->left){
    x->parent->left =y;
  }else{
    x->parent->right=y;
  }
  y->right=x;
  x->parent=y;
}

void RB_Insert_Fixup(Dictionary D, Node z){
  Node p = z->parent;
  Node y;
  while (p->color == 1){
    if(p == (p->parent->left)){
      //printf("Parent is on the Left Side\n");
      y=p->parent->right;
      if(y->color == 1){
        //printf("Uncle is Red. Changing Parent & Uncle color to Black. Grandparent to red\n");
        p->color=0;
        y->color=0;
        p->parent->color=1;
        z=p->parent;
      }else{
        //printf("Uncle Is not Red\n");
        if(z==p->right){
          //printf("On right side of Parent->Rotate Left\n");
          z=p;
          Left_Rotate(D,z);
          p=z->parent;
        }else{
          //printf("On Left side of Parent->Rotate right\n");
        }
        //printf("Parent to black & Grandparent to red\n");
        p->color=0;
        p->parent->color=1;
        Right_Rotate(D,p->parent);
      }
    }else{
      //printf("Parent is on the Right Side\n");
      y=p->parent->left;
      if(y->color == 1){
        //printf("Uncle is Red. Changing Parent & Uncle color to Black. Grandparent to red\n");
        p->color=0;
        y->color=0;
        p->parent->color=1;
        z=p->parent;
      }else{
        //printf("Uncle Is not Red\n");
        if(z==p->left){
          //printf("On right side of Parent->Rotate Right\n");
          z=p;
          Right_Rotate(D,z);
          p=z->parent;
        }
        //printf("Parent to black & Grandparent to red\n");
        p->color=0;
        p->parent->color=1;
        Left_Rotate(D,p->parent);
      }
    }
    p = z->parent;
  }
  D->tree->parent=D->nil;
  D->tree->color=0;
}
// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
  Node x = D->tree;
  Node y = D->nil;
  int compare=0;
  if(getUnique(D) && (lookup(D,k) !=VAL_UNDEF)){
      return;
  }
  Node item = newNode(k,v);
  item->right =D->nil;
  item->left =D->nil;
  // printf("------------------------ Start Insert Operation ------------------------------------\n");
  // printf("Inserting Node: %s  %d\n", item->key,*(item->value));
  while(x != D->nil){
    y=x;
    compare = KEY_CMP(k,x->key);
    if(compare<0){
      x=x->left;
    }else{
      x=x->right;
    }
  }
  item->parent=y;
  // printf("Parent is: %s  %d\n", y->key,*(y->value));
  if(y == D->nil){
    item->parent=D->nil;
    D->tree=item;
  }else if(compare <0){
    y->left=item;
    // printf("Insterting Left\n");
  }else{
    // printf("Inserting Right\n");
    y->right=item;
  }
  D->size=D->size+1;
  RB_Insert_Fixup(D, item);
  //printf("------------------------ End Insert Operation ------------------------------------\n");
}

void transplant( Dictionary D, Node u, Node v){
  if( u->parent == D->nil){
    D->tree = v;
  }else if (u == (u->parent)->left){
    u->parent->left = v;
  }else{
    u->parent->right =v;
  }
  v->parent = u->parent;
}

void RB_Delete_Fixup (Dictionary D, Node x){
  Node w;
  while ((x != D->tree) && (x->color == 0)){
    if(x == x->parent->left){
      w=x->parent->right;
      if(w->color == 1){
        w->color=0;
        x->parent->color=1;
        Left_Rotate(D,x->parent);
        w=x->parent->right;
      }
      if(w->left->color == 0 && w->right->color == 0){
        w->color=1;
        x=x->parent;
      }else{
        if (w->right->color == 0){
          w->left->color =0;
          w->color = 1;
          Right_Rotate(D,w);
          w=x->parent->right;
        }
        w->color=x->parent->color;
        x->parent->color=0;
        w->right->color=0;
        Left_Rotate(D,x->parent);
        x=D->tree;
      }
    }else{
      w=x->parent->left;
      if(w->color == 1){
        w->color=0;
        x->parent->color=1;
        Right_Rotate(D,x->parent);
        w=x->parent->left;
      }
      if(w->left->color == 0 && w->right->color == 0){
        w->color=1;
        x=x->parent;
      }else{
        if (w->left->color == 0){
          w->right->color =0;
          w->color = 1;
          Left_Rotate(D,w);
          w=x->parent->left;
        }
        w->color=x->parent->color;
        x->parent->color=0;
        w->left->color=0;
        Right_Rotate(D,x->parent);
        x=D->tree;
      }
    }
  }
  D->tree->parent=D->nil;
  x->color=0;
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
  Node leaf = D->tree;
  int compare = KEY_CMP(k,leaf->key);
  int orig_color;
  Node holder;
  while(compare !=0){
    if(leaf ==  D->nil){
      return;
    }else if(compare >0){
      leaf = leaf->right;
    }else{
      leaf = leaf->left;
    }
    compare = KEY_CMP(k,leaf->key);
  }
  if(D->cursor ==leaf){
    D->cursor=D->nil;
  }

  holder=leaf;
  Node x;
  orig_color=holder->color;
  if( leaf ->left == D->nil){
    x=leaf->right;
    transplant(D, leaf, leaf->right);
  }else if(leaf->right == D->nil){
    x=leaf->left;
    transplant(D,leaf,leaf->left);
  }else{
    holder = treeMinimum(D, leaf->right);
    orig_color=holder->color;
    x=holder->right;
    if(holder->parent == leaf){
      x->parent=holder;
    }else{
      transplant(D,holder,holder->right);
      holder->right=leaf->right;
      (holder->right)->parent=holder;
    }
    transplant(D,leaf,holder);
    holder->left=leaf->left;
    holder->left->parent=holder;
    holder->color=leaf->color;
  }
  if(orig_color==0){
    RB_Delete_Fixup(D,x);
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
  while(D->tree->right !=D->nil || D->tree->left !=D->nil){
    if(pin->left !=D->nil){
      pin=pin->left;
    }else if(pin->right !=D->nil){
      pin=pin->right;
    }else{
      back=pin->parent;
      if(back->left ==pin){
        freeNode(&(back->left));
        back->left=D->nil;
      }else{
        freeNode(&(back->right));
        back->right=D->nil;
      }
      pin=back;
    }
  }
  freeNode(&(D->tree));
  D->tree=D->nil;
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
  D->cursor = treeMinimum(D,D->tree);
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
  D->cursor = treeMaximum(D,D->tree);
  return (D->cursor)->value;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
  if(D->dir == 0 || D->cursor ==D->nil){
    return KEY_UNDEF;
  }
  return (D->cursor)->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if(D->dir == 0|| D->cursor ==D->nil){
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
  // printf("Start Node: %s  %d\n", start->key,*(start->value));
  // if(start->left == D->nil){
  //   printf("Does Not have left Node\n");
  // }else{
  //   printf("Left Node Key: %s\n", start->left->key);
  // }
  // if(start->right == D->nil){
  //   printf("Does Not have Right Node\n");
  // }else{
  //   printf("Right Node Key: %s\n", start->right->key);
  // }
  if(D->dir==0 || (start->parent == D->nil && start->right ==D->nil)){
    D->dir=0;
    D->cursor=D->nil;
    // printf("Case 0: %s  %d\n", D->cursor->key,*(D->cursor->value));
    // printf("------------------------ End Next Operation ------------------------------------\n");
  return VAL_UNDEF;
  }else if((start->right == D->nil) && (start->left == D->nil) && (start == (start->parent)->left)){
    D->cursor = start->parent;
    // printf("Case 1: %s  %d\n", D->cursor->key,*(D->cursor->value));
    // printf("------------------------ End Next Operation ------------------------------------\n");
  }else if (start->right !=D->nil){
    start=start->right;
    if(start->left != D->nil){
      start=treeMinimum(D,start);
    }
    D->cursor=start;
    // printf("Case 2: %s %d\n", start->key,*(start->value));
    // printf("------------------------ End Next Operation ------------------------------------\n");
  }else{
    while(start->parent->right == start){
      start=start->parent;
      if(start == D->nil){
        D->dir=0;
        return VAL_UNDEF;
      }
    }
    // printf("Case 3: %s %d\n", start->key,*(start->value));
    // printf("------------------------ End Next Operation ------------------------------------\n");
    D->cursor=start->parent;
  }
    // printf("Case 3.3: %s  %d\n", (D->cursor)->key,*(D->cursor->value));
    // printf("------------------------ End Next Operation ------------------------------------\n");
    if(D->cursor==D->nil){
      return KEY_UNDEF;
    }
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
  if(D->size==0 || (start->parent == D->nil && start->left ==D->nil)){
    D->dir=0;
    return VAL_UNDEF;
  }else if((start->right == D->nil) && (start->left == D->nil) && (start == (start->parent)->right)){
    D->cursor = start->parent;
  // printf("Case 1: %s  %d\n", D->cursor->key,D->cursor->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  }else if (start->left !=D->nil){
    start =start->left;
    if(start->right != D->nil){
      start=treeMaximum(D,start);
    }
    D->cursor=start;
  // printf("Case 2: %s %d\n", start->key,start->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  }else{
    while((start->parent)->left == start){
      start=start->parent;
    //printf("Case 3 (Moving Up): %s  %d\n", start->key,start->value);
      if(start->parent == D->nil){
        D->dir=0;
        return VAL_UNDEF;
      }
    }
    D->cursor =start->parent;
  }
  // printf("Case 3.3: %s  %d\n", (D->cursor)->key,D->cursor->value);
  // printf("------------------------ End Next Operation ------------------------------------\n");
  if(D->cursor==D->nil){
    return KEY_UNDEF;
  }
  return D->cursor->value;
}


Node treeMinimum(Dictionary D, Node x){
  Node leaf =x;
  while (leaf->left != D->nil){
    leaf=leaf->left;
  }
  return leaf;
}
Node treeMaximum(Dictionary D, Node x){
  Node leaf =x;
  //printf("In tree Maximum \n");
  while (leaf->right != D->nil){
    leaf=leaf->right;
  //printf("Within Maxtre %s with %d\n", leaf->key,leaf->value);
  }
  return leaf;
}
// Other operations -----------------------------------------------------------
void preOrder(FILE* out, Dictionary D,Node x){
  if(x != D->nil ){
    fprintf(out,KEY_FORMAT,x->key);
    preOrder(out,D,x->left);
    preOrder(out,D,x->right);
  }
}





void postOrder(FILE* out, Dictionary D,Node x){
  Node start=treeMinimum(D,D->tree);
  if (D->tree->right == D->nil && D->tree->left==D->nil){
    fprintf(out,KEY_FORMAT,(D->cursor)->key);
  }else if (D->tree!=D->nil){
    while(1){
      if((start->right == D->nil) && (start->left == D->nil) && (start == (start->parent)->left)){
        fprintf(out,KEY_FORMAT,start->key);
        start = start->parent;
      }else if (start->right !=D->nil){
        start=start->right;
        if(start->left != D->nil){
          start=treeMinimum(D,start);
        }
      //  printf("Case 1: %s\n", start->key);
      }else{
        fprintf(out,KEY_FORMAT,start->key);
        while(start->parent->right == start){
          start=start->parent;
          fprintf(out,KEY_FORMAT,start->key);
          if(start->parent == D->nil){
            return;
          }
        }
        // printf("Case 3: %s %d\n", start->key,*(start->value));
        // printf("------------------------ End Next Operation ------------------------------------\n");
        start=start->parent;
      }
    }
  }
}
// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D,const char* ord){
  if(D->size>0 && D != NULL){
    if(KEY_CMP(ord,"in")==0){
      beginForward(D);
      while(D->cursor != D->nil){
        fprintf(out,KEY_FORMAT,(D->cursor)->key);
        next(D);
      }
    }else if (KEY_CMP(ord,"post")==0){
      postOrder(out,D,D->tree);
    }else if (KEY_CMP(ord,"pre")==0){
      preOrder(out,D,D->tree);
    }
  }
}

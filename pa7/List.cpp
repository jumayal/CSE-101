/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA7
* List.cpp
* List ADT
*********************************************************************************/
#include<string>
#include<iostream>
#include "List.h"

using namespace std;

List::Node::Node(int x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

List::List(){
  frontDummy =new Node(0);
  backDummy =new Node(0);
  frontDummy->next=backDummy;
  backDummy->prev=frontDummy;
  beforeCursor=frontDummy;
  afterCursor=backDummy;
  pos_cursor=0;
  num_elements=0;

}

List::List(const List &L){
  Node* N;
  Node* M;

  backDummy=new Node(0);
  pos_cursor=0;
  num_elements=0;
  if(L.num_elements>0){
    N=L.frontDummy;
    M= new Node(N->data);
    frontDummy=M;
    M=frontDummy;
    while(N->next != L.backDummy){
      N=N->next;
      M->next=new Node(N->data);
      M->next->prev=M;
      M = M->next;
    }
    num_elements=L.num_elements;
    M->next=backDummy;
    backDummy->prev=M;
  }else{
    frontDummy = new Node(0);
    frontDummy->next=backDummy;
    backDummy->prev=frontDummy;
  }
  beforeCursor=frontDummy;
  afterCursor=frontDummy->next;
}


List::~List(){
  moveFront();
  while(num_elements >0){
    eraseAfter();

  }
  delete frontDummy;
  delete backDummy;
}

bool List::isEmpty(){
  if(num_elements ==0){
    return true;
  }
  return false;
}

int List::size(){
  return num_elements;
}

int List::position(){
  return (pos_cursor);
}

void List::moveFront(){
  beforeCursor=frontDummy;
  afterCursor=frontDummy->next;
  pos_cursor=0;
}

void List::moveBack(){
  beforeCursor=backDummy->prev;
  afterCursor=backDummy;
  pos_cursor=num_elements;
}

int List::peekNext (){
  if(pos_cursor==num_elements){
    cerr << "List Error: peeking at back DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  return afterCursor->data;
}

int List::peekPrev(){
  if(pos_cursor==0){
    cerr << "List Error: peeking at front DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  return beforeCursor->data;
}

int List::moveNext(){
  if(pos_cursor==num_elements){
    cerr << "List Error: moving into back DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  beforeCursor=afterCursor;
  afterCursor=afterCursor->next;
  pos_cursor++;
  //cout<<"The value:"<<beforeCursor->data<<endl;
  return beforeCursor->data;
}

int List::movePrev(){
  //cerr << "Before: " << beforeCursor->data << " After: " << afterCursor-> data<< " Position: " << pos_cursor<< endl;

  if(pos_cursor==0){
    cerr << "List Error: moving into front DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  afterCursor=beforeCursor;
  beforeCursor=beforeCursor->prev;
  pos_cursor--;

  return afterCursor->data;
}

void List::insertAfter(int x){
  Node* node = new Node(x);
  node->prev= beforeCursor;
  node->next = afterCursor;
  beforeCursor->next = node;
  afterCursor->prev = node;
  afterCursor=node;
  num_elements++;
}

void List::insertBefore(int x){
  Node* node = new Node(x);
  node->prev= beforeCursor;
  node->next = afterCursor;
  beforeCursor->next = node;
  afterCursor->prev = node;
  beforeCursor=node;
  pos_cursor++;
  num_elements++;
}

void List::eraseAfter(){
  if(pos_cursor==num_elements){
    cerr << "List Error: Erasing back DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  Node* N = afterCursor;
  beforeCursor->next=afterCursor->next;
  afterCursor->next->prev = beforeCursor;
  afterCursor=afterCursor->next;
  num_elements--;
  delete N;
}

void List::eraseBefore(){
  if(pos_cursor==0){
    cerr << "List Error: Erasing front DummyNode" << endl;
    exit(EXIT_FAILURE);
  }
  Node* N = beforeCursor;
  beforeCursor->prev->next=afterCursor;
  afterCursor->prev = beforeCursor->prev;
  beforeCursor=beforeCursor->prev;
  pos_cursor--;
  num_elements--;
  delete N;
}

int List::findNext(int x){
  //cerr << "Before: " << beforeCursor->data << " After: " << afterCursor-> data<< " Position: " << pos_cursor<< endl;
  while(afterCursor != backDummy){
    //cerr<<"Is "<<beforeCursor->data <<" equal to "<<x<<endl;
    moveNext();
    if(beforeCursor->data == x){
      return pos_cursor;
    }
  //  cerr << "Before: " << beforeCursor->data << " After: " << afterCursor-> data<< " Position: " << pos_cursor<< endl;
  }
  // if(beforeCursor->data == x){
  //   return pos_cursor;
  // }
  return -1;
}

int List::findPrev(int x){
  //cerr << "Before: " << beforeCursor->data << " After: " << afterCursor-> data<< " Position: " << pos_cursor<< endl;
  //movePrev();
  while(beforeCursor != frontDummy){
    movePrev();
    //cerr << "Before: " << beforeCursor->data << " After: " << afterCursor-> data<< " Position: " << pos_cursor<< endl;

    //cerr<<"Is "<<afterCursor->data <<" equal to "<<x<<endl;

    if(afterCursor->data == x){
      //eraseAfter();
      return pos_cursor;
    }
  }
  // if(afterCursor->data == x){
  //   //eraseAfter();
  //   return pos_cursor;
  // }
  return -1;
}

void List::cleanup(){
  Node* X = frontDummy;
  Node* Y;
  Node* deleted;
  int buffer;
  int current_pos=0;
  for(int i =0;i<num_elements;i++){
    current_pos=i+1;;
    X=X->next;
    buffer = X->data;
    Y=X->next;;
    while(Y != backDummy){
      if(Y->data == buffer){
        deleted = Y;
        Y->prev->next=Y->next;
        Y->next->prev = Y->prev;
        if(beforeCursor == Y){
          beforeCursor=Y->prev;
        }else if(afterCursor == Y){
          afterCursor=Y->next;
        }
        if(current_pos<pos_cursor){
          pos_cursor--;
        }
        current_pos--;
        Y=Y->prev;
        num_elements--;
        delete deleted;
      }
      Y=Y->next;
      current_pos++;
    }
  }
}

void List::clear(){
  moveFront();
  while(afterCursor != backDummy){
    eraseAfter();
  }
}

List List::concat(const List& L){
  List A= *this;
  A.moveBack();
  Node* start = L.frontDummy->next;
  for(int i=0;i<L.num_elements;i++){
    A.insertAfter(start->data);
    A.moveNext();
    start=start->next;
  }
  A.moveFront();
  return (A);
}

string List::to_string(){
  string s="";
  Node* A = frontDummy->next;
  s+="(";
  s+=std::to_string(A->data);
  if(A!=backDummy){
    A=A->next;
  }
  while(A != backDummy){
    s+=" "+std::to_string(A->data);
    A=A->next;
  }
  s+=")";
  return s;
}

bool List::equals(const List& R){
  bool eq = false;
  Node* M;
  Node* N;
  N= frontDummy->next;
  M=R.frontDummy->next;
  eq =(num_elements == R.num_elements);
  while(eq && N != backDummy){
    eq = (N->data == M->data);
    N=N->next;
    M = M->next;
  }
  return eq;
}

ostream& operator<<( std::ostream& stream, List& L ){
  return stream << L.List::to_string();
}

bool operator==( List& A, const List& B ){
  return A.List::equals(B);
}

List& List::operator=(const List& L){
  if(this != &L){
    List temp (L);
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
  }
  return *this;
}

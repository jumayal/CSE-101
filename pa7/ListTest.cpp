/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA7
* ListTest.cpp
* List test Client
*********************************************************************************/
#include<iostream>
#include<string>
#include "List.h"
using namespace std;

int main(int argc, char const *argv[]) {
   List A;
   List B;
  List C;

  for(int i=0; i<20;i++){
    A.insertAfter(19-i);
    B.insertBefore(i);
  }
  cout << "A = " << A << endl;
  cout << "B = " << B << endl;
  if(!A.equals(B)){
    cout<<"Error with equals"<<endl;
  }
  if(A.position() !=0 || A.size()!=20){
    cout<<"Error with insertAfer"<<endl;
  }
  if(B.position() !=20 || B.size()!=20){
    cout<<"Error with insertBefore"<<endl;
  }
  if(!C.isEmpty()){
    cout<<"Error with isEmpty"<<endl;
  }

  A.moveNext();
  if(A.moveNext() !=1){
    cout<<"Error with moveFront"<<endl;
  }
  if(A.peekPrev() != 1){
    cout<<"Error with peekPrev"<<endl;
  }

  A.eraseBefore();
  if(A.peekPrev() == 1){
    cout<<"Error with eraseBefore"<<endl;
  }
  //cout << "A = " << A << endl;

  if(A.findNext(19) != 19){
    cout<<"Error with Find Next "<<endl;
  }

  B.movePrev();
  B.movePrev();
  if(B.movePrev() != 17){
    cout<<"Error with moveBack"<<endl;
  }
  if(B.peekNext() !=17){
    cout<<"Error with peekNext"<<endl;
  }
  B.eraseAfter();
  if(B.peekNext() == 17){
    cout<<"Error with eraseAfter"<<endl;
  }
  if(B.findPrev(0) != 0){
    cout<<"Error with Find pprev"<<endl;
  }

  C=A;
  if(!A.equals(C)){
    cout<<"Error with ="<<endl;
  }

  A=A.concat(A);
  A.cleanup();
  if(!A.equals(C)){
    cout<<"Error with cleanup and/or concat"<<endl;
  }
  B.moveFront();
  if(B.peekNext()!=0){
    cout<<"Error with movefront"<<endl;
  }
  A.moveBack();
  if(A.peekPrev()!=19){
    cout<<"Error with moveBack"<<endl;
  }

  B.clear();
  if(B.size() !=0){
    cout<<"Error with cleanup size"<<endl;
  }
}

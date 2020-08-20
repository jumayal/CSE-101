/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA7
* Shuffle.cpp
* Takes a number input and creates a list up to that number. Counts the amount of
* times to shuffle
*********************************************************************************/
#include "List.h"
#include<iostream>
#include<string>

using namespace std;
#define MAX_LEN 300
void shuffle (List& deck);
int main(int argc, char const *argv[]) {
  string line;
  string tokenBuffer;
  int numCards;
  List deck;
  List shuffledDeck;
  int numShuffles;
  int spaceThreshold=10;
  int numSpace=15;

  // check command line for correct number of arguments
  if( argc != 2 ){
    cerr << "Usage: " << argv[0] << " <# of cards> <outputfile>" << endl;
    return(EXIT_FAILURE);
  }
  //Takes the number of cards
  numCards = stoi(argv[1]);

  //creates deck by the number of card input
  if(numCards>0){
    cout<<"deck size       shuffle count"<<endl;
    cout<<"------------------------------"<<endl;
    cout<<" 1"<<"               1"<<endl;
    cout<<" 2"<<"               2"<<endl;
    deck.insertBefore(0);
    deck.insertBefore(1);
    for(int i =2;i<numCards;i++){
      deck.insertBefore(i);
      shuffledDeck=deck;
      //cout<<"Deck = "<< deck<<endl;
      shuffle(shuffledDeck);
      //cout<<"shuffled Deck = "<< shuffledDeck<<endl;
      numShuffles=1;
      //cout<<"Deck = "<< deck<<endl;
      while(!shuffledDeck.equals(deck)){
        shuffle(shuffledDeck);
        //cout<<"shuffled Deck = "<< shuffledDeck<<endl;
        numShuffles++;
      }
      cout<<" "<<i+1;
      if(i==spaceThreshold-1){
        numSpace--;
        spaceThreshold=spaceThreshold*10;
      }
      for(int j =0;j<numSpace;j++){
        cout<<" ";
      }
      cout<<numShuffles<<endl;
    }
  }
  // cout<<"Deck = "<< deck<<endl;
  // List shuffledDeck= shuffle(deck);
  // cout<<"shuffled Deck = "<< shuffledDeck<<endl;
  return 0;
}

void shuffle(List& deck){
  List firstHalf;
  List secondHalf;
  int numOfCards = deck.size();
  int halfNum=numOfCards/2;

  deck.moveFront();
  for(int i=0; i<halfNum;i++){
    firstHalf.insertBefore(deck.moveNext());
  }
  for(int j =numOfCards/2;j<numOfCards;j++){
    secondHalf.insertBefore(deck.moveNext());
  }
  // cout<<"FirstHalf= "<<firstHalf<<endl;
  // cout<<"secondHalf="<<secondHalf<<endl;
  // cout<<"Deck="<<deck<<endl;
  // cout<<"HalfNume:"<<halfNum<<endl;
  firstHalf.moveFront();
  secondHalf.moveFront();
  deck.clear();
  deck.moveFront();
  for(int k=0;k<halfNum;k++){
    deck.insertBefore(secondHalf.moveNext());
    //cout<<"First portion perfect half shuffle="<<deck<<endl;
    deck.insertBefore(firstHalf.moveNext());
      //cout<<"second Portion perfect half shuffle="<<deck<<endl;
  }
  //cout<<"After perfect half shuffle="<<deck<<endl;
  if(halfNum *2 != numOfCards){
    deck.insertBefore(secondHalf.moveNext());
  }
}

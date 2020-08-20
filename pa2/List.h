/*********************************************************************************
* Juan Ayala, jumaayal
* 2020 Spring CSE101 PA1
* List.h
* List ADT header file
*********************************************************************************/
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
//Definitions-----------------------------------------------------------------------

#define ELEMENT_TYPE long //int

// Exported type --------------------------------------------------------------
typedef struct listObj* List;

// Constructors-Destructors ---------------------------------------------------

/*Creates a new list*/
List newList(void);

/*Removes List from memory*/
void freeList(List* pL);
// Access functions -----------------------------------------------------------
/*Returns length of list*/
int length(List L);

/*Returns index cursor on list
*Returns -1 if outof bounds*/
int index(List L);

/*Returns item in front of list
*Exits program if front item is NULL*/
ELEMENT_TYPE front(List L);

/*Returns item from back of list
*Exits program if back item is NULL*/
ELEMENT_TYPE back(List L);

/*Returns item at index*/
ELEMENT_TYPE get(List L);

/*Compares two List structures
*returns 1 if equal
**returns 0 if not equal*/
int ls_equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
/*Clears items on list and returns index to 0*/
void clear(List L);

/*Index is 0*/
void moveFront(List L);

/*Index is at length-1 of array*/
void moveBack(List L);

/*Decrements Index*/
void movePrev(List L);

/*Increments Index*/
void moveNext(List L);

/*Adds item to front of list*/
void prepend(List L, ELEMENT_TYPE data);

/*Adds item to back of list*/
void append(List L, ELEMENT_TYPE data);

/*Inserts item before index*/
void insertBefore(List L, ELEMENT_TYPE data);

/*Inserts item after index*/
void insertAfter(List L, ELEMENT_TYPE data);

/*Delets node at front of list*/
void deleteFront(List L);

/*Delets node at back of list*/
void deleteBack(List L);

/*Compares two List structures*/
void delete(List L);

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, ELEMENT_TYPE x);
// Other operations -----------------------------------------------------------
/*Prints List on a file*/
void printList(FILE* out, List L);

/*Creates a new list with same contents of list*/
List copyList(List L);

#endif

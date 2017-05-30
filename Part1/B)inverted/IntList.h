// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008
// Modified by Aldhytha Karina Sari, 21/05/2017
//
// Removed the following functions:
// -void IntListInsertInOrder(IntList L, int v)
// -IntList IntListCopy(IntList L)
// -IntList IntListSortedCopy(IntList L)
// -int IntListIsSorted(IntList L)
// -int IntListOK(IntList L)
// -void IntListPrint(FILE *outf, IntList L)
// 
// Changed from doubly linked list to singly linked list
// Changed the following functions:
// -void showIntList(FILE* fp, IntList L)
// -void freeIntList(IntList L) function
// -void IntListInsert(IntList L, int v)
// -void IntListDelete(IntList L, int v) to void IntFirstDelete(IntList L)
//
// Added int findNode (IntList L, int v) function

#ifndef INTLIST_H
#define INTLIST_H

#include <stdio.h>

// External view of IntList
// Implementation given in intList.c

typedef struct IntListRep *IntList;

// create a new empty IntList
IntList newIntList();

// free up all space associated with list
void freeIntList(IntList);

// display list as one integer per line on stdout
void showIntList(FILE*, IntList);

// append one integer to the end of a list
void IntListInsert(IntList, int);

// find the integer value in the list
int findNode (IntList L, int v);

// delete head of list
void IntFirstDelete(IntList);

// return number of elements in a list
int IntListLength(IntList);

// display list as one integer per line to a file
// assume that the file is open for writing
void IntListPrint(IntList);

#endif
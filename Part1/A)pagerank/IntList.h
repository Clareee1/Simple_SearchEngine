// IntList.h - Lists of integers (interface)
// Written by John Shepherd, July 2008
// Modified by Aldhytha Karina Sari, 21/05/2017

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

//find Node
int findNode (IntList L, int v);

// delete head of list
void IntFirstDelete(IntList);

// return number of elements in a list
int IntListLength(IntList);

// display list as one integer per line to a file
// assume that the file is open for writing
void IntListPrint(IntList);

#endif

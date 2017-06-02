// list.h - Lists of integers (interface)
// Written by John Shepherd (IntList.h), July 2008
// Modified by Aldhytha Karina Sari, 01/06/2017
//
// Removed the following functions:
// -void IntListInsertInOrder(IntList L, int v)
// -IntList IntListCopy(IntList L)
// -IntList IntListSortedCopy(IntList L)
// -int IntListIsSorted(IntList L)
// -int IntListOK(IntList L)
// -void IntListPrint(FILE *outf, IntList L)
// -void showIntList(FILE* fp, IntList L)
// 
// Changed from doubly linked list to singly linked list
// Changed the following functions:
// -void freeIntList(IntList L) function
// -void IntListInsert(IntList L, int v)
// -void IntListDelete(IntList L, int v) to void IntFirstDelete(IntList L)
//
// Added the following functions:
// -node newIntListNode(double, int);
// -void insertNode(node, int, double);
// -double addition (int value, int position, int size, IntList);
// -double calculateMinDist (IntList L, int * original, int * result, int size);
// -int * minimumPosition (IntList L, int * combined, int num);
// Local:
// -void arrayCopy (double*, double*, int);
// -void mergesort(int* array, int lo, int hi, double* PRarray);
// -void merge(int* array, int lo, int mid, int hi, double* PRarray);

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

// External view of IntList
// Implementation given in list.c

//let the node be accessed by the main function
typedef struct IntListNode * node;
typedef struct IntListRep *IntList;

// create a new empty IntList
IntList newIntListP3();
// create a new node
node newIntListNode(double, int);
// insert the data array inside a node
void insertNode(node, int, double);
// free up all space associated with list
void freeIntListP3(IntList);
// display list as one integer per line on stdout
void showIntListP3(IntList, int);
// append one node to the end of a list
void IntListInsertP3(IntList, node);
// delete head of list
void IntFirstDeleteP3(IntList);
// return number of elements in a list
int IntListLengthP3(IntList);
// to calculate the distance of a certain value by a certain position
double addition (int value, int position, int size, IntList);
// calculate the minimum distance of each position from array result to array original
// uses the scaled footrule formula
double calculateMinDist (IntList L, int * original, int * result, int size);
// calculate the first minimum position using the midpoint formula (average point)
int * minimumPosition (IntList L, int * combined, int num);

#endif

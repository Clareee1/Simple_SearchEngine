// IntList.c - Lists of integers
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

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "IntList.h"

// data structures representing IntList
typedef struct IntListNode * node;
struct IntListNode {
	int data;  // value of this list item
	int howMany;
	struct IntListNode *next;
	            // pointer to node containing next element
};

struct IntListRep {
	int size;  // number of elements in list
	struct IntListNode *first;
	            // node containing first value
};

// create a new empty IntList
IntList newIntList()
{
	struct IntListRep *L;
	L = malloc(sizeof (struct IntListRep));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	return L;
}

// free up all space associated with list
void freeIntList(IntList L)
{
	while (L->first != NULL) {
		IntFirstDelete(L);
	}
	free (L);
}

// display list as one integer per line on stdout
void showIntList(FILE* fp, IntList L)
{
	assert(L != NULL);
	struct IntListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next)
	fprintf(fp, "url%d ", curr->data);
	fprintf(fp, "\n");
}

// create a new IntListNode with value v
// (this function is local to this ADT)
static struct IntListNode *newIntListNode(int v)
{
	struct IntListNode *n;
	n = malloc(sizeof (struct IntListNode));
	assert(n != NULL);
	n->data = v;
	n->howMany = 1;
	n->next = NULL;
	return n;
}

// append one integer to the end of a list
void IntListInsert(IntList L, int v)
{
	assert(L != NULL);
	if (findNode (L, v) == 0) return;
	struct IntListNode *n;
	n = newIntListNode(v);
	if (L->first == NULL)
		L->first = n;
	else {
		node curr = L->first;
		while (curr->next != NULL) {
			curr = curr->next;
		}
 		curr->next = n;
	}
	L->size++;
}

// find value in the list
// return 0 if it's in the list, 1 if it's not
int findNode (IntList L, int v) {
	assert (L != NULL);
	node curr = L->first;
	while (curr != NULL) {
		if (curr->data == v) {
			curr->howMany++;
			return 0;
		} //else
		curr = curr->next;
	}
	return 1;
}

// delete the head of the list
void IntFirstDelete(IntList L)
{
	struct IntListNode *curr;
	assert(L != NULL);
	// find where v occurs in list
	curr = L->first;
	L->first = curr->next;
	L->size--;
	// remove curr
	free(curr);
}

// return number of elements in a list
int IntListLength(IntList L)
{
	assert(L != NULL);
	return L->size;
}
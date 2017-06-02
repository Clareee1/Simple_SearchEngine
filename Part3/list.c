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
// -void mergesort(int* array, int lo, int hi, double* PRarray);
// -void merge(int* array, int lo, int mid, int hi, double* PRarray);


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "assert.h"
#include "list.h"

// data structures representing IntList
typedef struct IntListNode * node;
struct IntListNode {
	// value of this list item
	double * data;
	double numOfUrl;
	// pointer to node containing next element
	struct IntListNode *next;
};

struct IntListRep {
	// number of elements in list
	int size;  
	// node containing first value
	struct IntListNode *first;
};

//--------------------------------------------------------------------------------------
// the auxiliary function for mergesort (from Lecture)
void mergesort(int* array, int lo, int hi, double* PRarray);
// ascending merge sort (From Lecture, modified by Hui Min Wang)
void merge(int* array, int lo, int mid, int hi, double* PRarray);
//--------------------------------------------------------------------------------------

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
void showIntList(IntList L, int num)
{
	assert(L != NULL);
	struct IntListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next) {
		int i;
		for (i = 0; i < num; i++) {
			printf("%.5f ", curr->data[i]);
		}
		printf("\n");
	}
}

// create a new IntListNode with value v
struct IntListNode *newIntListNode(double length, int num)
{
	struct IntListNode *n;
	n = malloc(sizeof (struct IntListNode));
	assert(n != NULL);
	n->data = malloc (sizeof (double) * num);
	int i;
	for (i = 0; i < num; i++) {
		n->data[i] = (double)0;
	}
	n->numOfUrl = length;
	n->next = NULL;
	return n;
}

// insert the data array inside a node
// each node represents each .txt file
void insertNode(node n, int index, double num)
{
	n->data[index] = num;
	return;
}

// append one integer to the end of a list
void IntListInsert(IntList L, node n)
{
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
	free(curr->data);
	free(curr);
}

// return number of elements in a list
int IntListLength(IntList L)
{
	assert(L != NULL);
	return L->size;
}

// calculate the minimum distance of each position from array result to array original
// uses the scaled footrule formula
double calculateMinDist (IntList L, int * original, int * result, int size)
{
	//create an array of position of p
	int p[size];
	double distance = (double) 0;
	struct IntListNode *curr;
	int i, j;
	for (i = 0; i < size; i++) {
		// find position for every element in the array
		for (j = 0; j < size; j++) {
			if (original[i] == result[j]) {
				p[i] = j+1;
			}
		}
		// calculate the distance for every node
		for (curr = L->first; curr != NULL; curr = curr->next) {
			if (curr->data[i] != 0) {
				distance = distance + fabs(curr->data[i] - (double)p[i]/(double)size);
			}
		}
	}
	return distance;
}

// to calculate the distance of a certain value by a certain position
double addition (int value, int position, int size, IntList L) {
	double sum = 0;
	//same lines as the second double nested loop in the above function
	struct IntListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next) {
		if (curr->data[value] != 0) {
			sum = sum + fabs (curr->data[value] - (double)(position + 1)/size);
		}
	}
	return sum;
}

// calculate the first minimum position using the midpoint formula (average point)
int * minimumPosition (IntList L, int * array, int num) {
	assert (L != NULL);
	// make an array of doubles and set them to 0
	double dist[num];
	int i;
	for (i = 0; i < num; i++) {
		dist[i] = (double)0;
	}
	//midpoint formula (or average point)
	struct IntListNode *curr;
	for (i = 0; i < num; i++) {
		//to count how many files do the url exist
		int count = 0;
		for (curr = L->first; curr != NULL; curr = curr->next) {
			if (curr->data[i] != (double) 0) {
				count++;
				dist[i] = dist[i] + curr->data[i];
			}
		}
		dist[i] = dist[i]/ (double) count;
	}
	//sort the union array of urls and dist in an ascending order of distance
	mergesort(array, 0, num-1, dist);
	return array;
}

// the auxiliary function for mergesort (from Lecture)
void mergesort(int* array, int lo, int hi, double* PRarray) {
    if(hi <= lo) return;
    int mid = (lo + hi)/2;
    mergesort(array, lo, mid, PRarray);
    mergesort(array, mid+1, hi, PRarray);
    merge(array, lo, mid, hi, PRarray);
}

// ascending merge sort (From Lecture, modified by Hui Min Wang)
void merge(int* array, int lo, int mid, int hi, double* PRarray) {
    int i, j, k, nitems = hi-lo+1;
    double* tmp = malloc(nitems*sizeof(double));
    int* tmp2 = malloc(nitems*sizeof(int));

    i = lo; j = mid + 1; k = 0;
    while( i <= mid && j <= hi){
        if(PRarray[i] < PRarray[j]){
            tmp[k] = PRarray[i]*1.00000;
            tmp2[k] = array[i];
            k++;
            i++;
        } else {
            tmp[k] = PRarray[j] * 1.00000;
            tmp2[k] = array[j];
            k++;
            j++;
        }
    }

    while (i <= mid){
        tmp[k] = PRarray[i];
        tmp2[k] = array[i];
        i++;
        k++;
    }

    while (j <= hi){
        tmp[k] = PRarray[j];
        tmp2[k] = array[j];
        k++;
        j++;
    }

    for(i = lo, k = 0; i <= hi; i++, k++){
        array[i] = tmp2[k];
        PRarray[i] = tmp[k];
    }

    free(tmp2);
    free(tmp);
}
// scaledFootrule.c
// created by Aldhytha Karina Sari (Alina) 01/06/2017
//
// how it works:
// -set an initial minimum position and calculate its distance
//  (using the midpoint formula (average point) to get an estimation
//  that's similar to the actual position)
// -iterate through the complete (undirected) graph via hamilton path
//  by comparing each step with the minimum distance and ignore those
//  that exceed the distance
// -print the result
// -this program will process data really fast
//  if the average point of the data doesn't clash with each other
//  and is similar to the actual minimum distance points.
//  i.e. having a similar position for each txt files
//  (urls are in ascending order)
// -time performance increases/decreases (almost) exponentially depending on the input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "parser.h"
#include "list.h"

#define BUFFER 64
#define MAX_URL 100
#define FALSE 0
#define TRUE 1

//normalise argv (remove duplicate inputs)
char ** normalisedArgv (int * argc, char * argv[]);
//free the normalised argv
void freeArgv (int argc, char * argv[]);
//process all of the files/data
void getUnionData (int *, int, char**);
//insert the data to a list
void insertData (IntList, int *, int, int, char**);
//get a union of the data
void arrayUnion (int *, int *, int, int);
//mallocked an array
int * createArray (int);
//duplicate array
void arrayCopy (int *, int *, int);
//return the size of an array
int sizeOfArray (int *);
//print array
void printArray (int *, int);
//create graph
void insertGraph (Graph, int);
//iterate through path
double findMinimum (Graph, IntList, int *, int *, double, int);

int main (int argc, char * argv[]) {
	if (argc > 1) {
		//normalise argv in case the input contains duplicates
		char ** newArgv = normalisedArgv (&argc, argv);
		//create an array for the union of urls
		int * combined = createArray (MAX_URL);
		getUnionData (combined, argc, newArgv);
		int size = sizeOfArray (combined);
		if (size == 0) {
			free(combined);
			freeArgv (argc, newArgv);
			exit (EXIT_SUCCESS);	
		} 
		//create a new list
		IntList L = newIntList();
		insertData (L, combined, size, argc, newArgv);
		freeArgv (argc, newArgv);

		//create an array for the minimum location
		int * minDistArray = createArray (size);
		//copy the union into the minimum location
		arrayCopy (minDistArray, combined, size);
		//change the position of the elements
		minDistArray = minimumPosition (L, minDistArray, size);
		//calculate the current minimum distance
		double currDist = calculateMinDist (L, combined, minDistArray, size);

		//create a graph
		Graph g = newGraph(size);
		insertGraph (g, size);
		currDist = findMinimum (g, L, combined, minDistArray, currDist, size);

		//print result
		printf("%.6f\n", currDist);
		printArray (minDistArray, size);

		//free everything
		freeIntList (L);
		dropGraph(g);
		free (combined);
		free (minDistArray);
	}
	return EXIT_SUCCESS;
}

//normalise the argv input in case there are duplicates
char ** normalisedArgv (int * num, char * argv[]) {
	int i, j;
	int count = 0;
	char ** array = malloc (sizeof (char**) * (*num));
	//mallocked a new array of strings
	for (i = 0; i < *num; i++) {
		for (j = 0; j < count; j++) {
			if (strcmp (argv[i], array[j]) == 0) break;
		}
		if (j >= count) {
			array[count] = strdup(argv[i]);
			count++;
		}
	}
	//change the value of num in the calling function to length of array
	*num = count;
	return array;
}

//free the normalised argv
void freeArgv (int num, char * array[]) {
	int i;
	for (i = 0; i < num; i++) free(array[i]);
	free (array);
}


//process all of the files/data
void getUnionData (int * array, int argc, char * argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		//get the number of urls and their names from each file in the input
		int arraySize = getNumOfUrlFromFile(argv[i]);
		if (arraySize == 0) continue;
		int * urlArray = getNameOfUrlFromFile(argv[i], arraySize);
		//combined the found urls to 'array'
		arrayUnion (array, urlArray, MAX_URL, arraySize);
		//free mallocked memory
		free(urlArray);
	}
}

//insert the data to a list
void insertData (IntList L, int * array, int size, int argc, char * argv[]) {
	int i, j;
	for (i = 1; i < argc; i++) {
		//get the number of urls and their names from each file in the input
		int arraySize = getNumOfUrlFromFile(argv[i]);
		if (arraySize == 0) continue;
		int * urlArray = getNameOfUrlFromFile(argv[i], arraySize);
		//create a new node
		node n = newIntListNode((double)arraySize, size);
		//insert values to node
		int k;
		for (j = 0; j < arraySize; j++) {
			for (k = 0; k < size; k++) {
				if (array[k] == urlArray[j]) insertNode (n, k, (double) (j + 1)/arraySize);
			}
		}
		//insert node to list
		IntListInsert(L, n);
		//free mallocked memory
		free(urlArray);
	}
}
//mallocked an array
int * createArray (int size) {
	//mallcoked an array & check memory
	int * array = malloc (size * sizeof (int));
	if (array == NULL) {
		exit (EXIT_FAILURE);
	}
	//set all values to -1
	int i;
	for (i = 0; i < size; i++) {
		array[i] = -1;
	}
	//return the mallocked array
	return array;
}

//duplicate array
void arrayCopy (int * result, int * input, int sizeInput) {
	int i;
	for (i = 0; i < sizeInput; i++) {
		result[i] = input[i];
	}
}

//return the size of an array
int sizeOfArray (int * array) {
	int size;
	for (size = 0; array[size] != -1; size++);
	return size;
}

//combined array input to array result
void arrayUnion (int * result, int * input, int resultSize, int inputSize) {
	int i, j;
	for (i = 0; i < inputSize; i++) {
		//if the value exists, do nothing
		for (j = 0; result[j] != -1 && j < resultSize; j++) {
			if (result[j] == input[i]) {
				break;
			}
		}
		//if the value doesn't exist, add it to the end of the result array
		if (result[j] == -1) {
			result[j] = input[i];
		}
	}
}

//print array
void printArray (int * array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("url%d\n", array[i]);
	}
}

//create graph
void insertGraph (Graph g, int size) {
	//insert edges to make a complete graph
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i != j) insertEdge(g, i, j, 1);
		}
	}
}

double findMinimum (Graph g, IntList L, int * combined, int * minDistArray, double currDist, int size) {
	//mallocked an array for location
	int * location = calloc (size + 1, sizeof(int));
	int i;
	for (i = 0; i < size; i++) {
		//iterating through the graph
		double distance = HamiltonPath(g, i, currDist, combined, L, location);
		if (location[size] == TRUE) {
			currDist = distance;
			//copy the location array to minDistArray
			arrayCopy (minDistArray, location, size);
		}
	}
	//free
	free (location);
	return currDist;
}
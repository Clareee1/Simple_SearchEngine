//searchPagerank.c
// Written by Aldhytha Karina Sari (Alina), 26 May 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define TRUE 0
#define FALSE 1
#define MAX_URL 100
#define MAX_URL_TO_PRINT 10
#define MAX_BUFFER 64

int * createArray (int size);
void arrayUnion (int *, int *, int, int);
void printArray (int * array);

int main (int argc, char * argv[]) {

	if (argc > 2) {
		int * combined = createArray (MAX_URL);
		int counter;
		for (counter = 1; counter < argc; counter++) {
			if (hasKeyword ("invertedIndex.txt", argv[counter]) == 0) {
				exit(EXIT_SUCCESS);
			} 

			int arraySize = getNumOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter]);
			int * urlArray = createArray (arraySize);
			getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter], urlArray);

			arrayUnion (combined, urlArray, MAX_URL, arraySize);

			free (urlArray);
		}
		printArray (combined);
   		free (combined);
	} else {
		exit (EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}

int * createArray (int size) {
	int * array = malloc (size * sizeof (int));
	if (array == NULL) {
		exit (EXIT_FAILURE);
	}
	int i;
	for (i = 0; i < size; i++) {
		array[i] = -1;
	}
	return array;
}

void arrayUnion (int * result, int * input, int resultSize, int inputSize) {
	int i, j;
	for (i = 0; i < inputSize; i++) {
		for (j = 0; result[j] != -1 && j < resultSize; j++) {
			if (result[j] == input[i]) {
				break;
			}
		}
		if (result[j] == -1) {
			result[j] = input[i];
		}
	}
}

void printArray (int * array) {
	FILE *fp = fopen ("pagerankList.txt", "r");
	if (fp == NULL) {
		printf("Out of Memory\n");
		exit (EXIT_FAILURE);
	}
	char buffer [MAX_BUFFER];
    while (fscanf(fp, "\n %s ", buffer) == 1) {
     	strlower(buffer);
        int i;
        int count = 0;
		for (i = 0; array[i] != -1; i++) {
     	   	char * tmp = getStringFromNum (array[i]);
    	    if (strstr(buffer, tmp) != NULL && count < MAX_URL_TO_PRINT) {
    	   		printf("%s\n", tmp);
    	   		count++;
	        }
	        free(tmp);
	    }
    }
	fclose (fp);
}
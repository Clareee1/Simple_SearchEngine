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
void arrayCopy (int * result, int * input, int sizeInput);
int arrayConjunction (int *, int *, int *, int, int);
void printArray (int * array, int size);

int main (int argc, char * argv[]) {

	if (argc > 2) {
		int * combined = createArray (MAX_URL);
		int combinedSize = 0;
		int counter;
		for (counter = 1; counter < argc; counter++) {
			if (hasKeyword ("invertedIndex.txt", argv[counter]) == 0) {
				exit(EXIT_SUCCESS);
			} 

			int arraySize = getNumOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter]);
			int * urlArray = createArray (arraySize);
			getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter], urlArray);
			
			if (counter == 1) {
				arrayCopy (combined, urlArray, arraySize);
				combinedSize = arraySize;
			} else {
				int * tmp = createArray (combinedSize);
				arrayCopy (tmp, combined, combinedSize);
				combinedSize = arrayConjunction (combined, tmp, urlArray, combinedSize, arraySize);
				free(tmp);
			}
			free (urlArray);
		}
		printArray (combined, combinedSize);
   		free (combined);
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

void arrayCopy (int * result, int * input, int sizeInput) {
	int i;
	for (i = 0; i < sizeInput; i++) {
		result[i] = input[i];
	}
}

int arrayConjunction (int * result, int * input1, int * input2, int arraySize1, int arraySize2) {
	int i, j;
	int length = 0;
	for (i = 0; i < arraySize1; i++) {
		for (j = 0; j < arraySize2; j++) {
			if (input1[i] == input2[j]) {
				result[length] = input1[i];
				length++;
			}
		}
	}
	return length;
}

void printArray (int * array, int size) {
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
		for (i = 0; i < size; i++) {
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
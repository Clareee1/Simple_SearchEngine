//searchPagerank.c
// Written by Aldhytha Karina Sari (Alina), 26 May 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define TRUE 0
#define FALSE 1
#define MAX_URL_TO_PRINT 10
#define MAX_BUFFER 64

int arrayConjunction (int *, int *, int *, int, int);

int main (int argc, char * argv[]) {
	if (argc == 3) {
		char * keyword1 = argv[1]; 
		char * keyword2 = argv[2];

		if ((hasKeyword("invertedIndex.txt", keyword1)) == 0 || (hasKeyword("invertedIndex.txt", keyword2)) == 0) {
			printf("Enter a valid keyword\n");
			exit(EXIT_SUCCESS);
		}

		int arraySize1 = getNumOfUrlForKeywordFromFile("invertedIndex.txt", keyword1);
		int urlArray1[arraySize1];
		getNameOfUrlForKeywordFromFile("invertedIndex.txt", keyword1, urlArray1);

		int arraySize2 = getNumOfUrlForKeywordFromFile("invertedIndex.txt", keyword2);
		int urlArray2[arraySize2];
		getNameOfUrlForKeywordFromFile("invertedIndex.txt", keyword2, urlArray2);

		int combinedSize;

		if ((arraySize1 < arraySize2) == TRUE) {
			combinedSize = arraySize1;
		} else {
			combinedSize = arraySize2;
		}

		int combined [combinedSize];

		combinedSize = arrayConjunction (combined, urlArray1, urlArray2, arraySize1, arraySize2);

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
            for (i = 0; i < combinedSize; i++) {
            	char * tmp = getStringFromNum (combined[i]);
	    	    if (strstr(buffer, tmp) != NULL && count < 10) {
	    	    	printf("%s\n", tmp);
	    	    	count++;
	    	    }
	    	    free(tmp);
		    }
    	}
		fclose (fp);
	} else {
		printf("Usage: ./searchPagerank [keyword1] [keyword2]\n");
	}
	return EXIT_SUCCESS;
}

int arrayConjunction (int * combined, int *array1, int *array2, int size1, int size2) {
	int i, j;
	int combinedSize = 0;
	for (i = 0; i < size1; i++) {
		for (j = 0; j < size2; j++) {
			if (array1[i] == array2[j]) {
				combined[combinedSize] = array1[i];
				combinedSize++;
			}
		}
	}
	return combinedSize;
}
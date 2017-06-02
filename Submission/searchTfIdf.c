//
//  searchTfIdf.c
//  Created by Henry Quan on 20/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"

// How to use this program
void showUsage();
// Calculate term frequency value for keyword in a url
double calTfValue(int count);
// Calculate inverse document frequency value for collection
double calIdfValue(int contained, int total);
// Calculate term frequency–inverse document frequency for keyword
double calTfidfValue(double tf, double idf);
// Create an integer array
int *newIntArray(int size);
// Create a double array
double *newDoubleArray(int size);
// Get index from urlArray
int getIndexFromArray(int *urlArray, int url, int size);
// Swap index for urlArray
void swapIndex(int *urlArray, int index1, int index2);
// Swap value for urlArray
void swapValue(double *resultArray, int index1, int index2);
// Get top ten from resultArray
void getTopTen(double *resultArray, int *urlArray, int size);
// Fatal error
void fatalError(char *message);
// Remove duplicates
void keywordsWithoutDuplicates(char *argv[], int argc);
// duplicate array
void arrayCopy(int *, int *, int);
// find intersection of arrays
int arrayConjunction(int *, int *, int *, int, int);
// New array
int *createArray(int size);

int main(int argc, char *argv[]) {
    // There has to be at least one words
    if (argc <= 1) showUsage();
    keywordsWithoutDuplicates(argv, argc);

    // Get the total number of urls we have in collection.txt for idf
    int totalUrlCount = getNumOfUrlFromFile("collection.txt");
    // Create another temp array with same size to hold temp url
    // int *tempArray = newIntArray(totalUrlCount);
    // if (tempArray == NULL) fatalError("Out of memory");

    // Make new array for the urls in the intersection of urls
    int *combined = createArray(100);
    int combinedSize = 0;
    int counter;
    for (counter = 1; counter < argc; counter++) {
        if (argv[counter] == NULL) continue;
        if (hasKeyword("invertedIndex.txt", argv[counter]) == 0) {
            free(combined);
            exit(EXIT_SUCCESS);
        }
        //get the array of url that contains the keyword
        int arraySize = getNumOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter]);
        if (arraySize == 0) {
            free(combined);
            exit(EXIT_SUCCESS);
        }
        int * urlArray = createArray(arraySize);
        getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[counter], urlArray);

        //adjust the combined array
        if (counter == 1) {
            arrayCopy(combined, urlArray, arraySize);
            combinedSize = arraySize;
        } else {
            int * tmp = createArray(combinedSize);
            arrayCopy(tmp, combined, combinedSize);
            combinedSize = arrayConjunction(combined, tmp, urlArray, combinedSize, arraySize);
            free(tmp);
        }

        //free the array of urls of one keyword
        free (urlArray);
    }

    // Create a double array of size totalUrlCount to hold result
    double *resultArray = newDoubleArray(combinedSize);
    if (resultArray == NULL) fatalError("Out of memory");

    int i, j;
    for (i = 1; i < argc; i++) {
        if (argv[i] != NULL) {
            if (!hasKeyword("invertedIndex.txt", argv[i])) continue;
            // Repeat for each keyword
            int urlWithKeyword = getNumOfUrlForKeywordFromFile("invertedIndex.txt", argv[i]);
            // getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[i], tempArray);
            double idf = calIdfValue(urlWithKeyword, totalUrlCount);
            // printf("c: %d, idf: %f\n", urlWithKeyword, idf);
            for (j = 0; j < combinedSize; j++) {
                // Repeat for each url
                char buffer[64]; // Store url full name
                sprintf(buffer, "url%d.txt", combined[j]);
                // Get term frequency
                int tf = getKeywordCountFromUrl(buffer, argv[i]);
                // Get index
                int index = getIndexFromArray(combined, combined[j], totalUrlCount);
                // printf("tf: %d, index: %d, idtdf: %f\n", tf, index, calTfidfValue(calTfValue(tf), idf));
                // Add this value to resultArray if valid
                if (index != -1) resultArray[index] += calTfidfValue(calTfValue(tf), idf);
            }
        }
    }

    // Sort resultArray
    getTopTen(resultArray, combined, combinedSize);
    for (i = 0; i < 10; i++) {
        if (i >= totalUrlCount) break;
        if (resultArray[i] < 0.000001) break;
        printf("url%d, %0.6f\n", combined[i], resultArray[i]);
    }

    free(combined);
    free(resultArray);

    return 0;
}

// mallocked new array
int *createArray (int size) {
	//mallocked a new array
	int * array = malloc (size * sizeof (int));
	if (array == NULL) {
		exit (EXIT_FAILURE);
	}
	//set all values to -1
	int i;
	for (i = 0; i < size; i++) {
		array[i] = -1;
	}
	return array;
}

// duplicate array
void arrayCopy (int * result, int * input, int sizeInput) {
	int i;
	for (i = 0; i < sizeInput; i++) {
		result[i] = input[i];
	}
}

// find intersection of arrays
int arrayConjunction (int * result, int * input1, int * input2, int arraySize1, int arraySize2) {
	int i, j;
	int length = 0;
	for (i = 0; i < arraySize1; i++) {
		for (j = 0; j < arraySize2; j++) {
			if (input1[i] == input2[j]) {
				//copy urls that are in both input arrays to result array
				result[length] = input1[i];
				length++;
			}
		}
	}
	return length;
}

// Remove duplicates
void keywordsWithoutDuplicates(char *argv[], int argc) {
    if (argv == NULL) return;

    int i, j, isDuplicate = 0;
    for (i = 1; i < argc; i++) {
        strlower(argv[i]);
    }

    for (i = 1; i < argc; i++) {
        for (j = 1; j < i; j++) {
            if (i == 1) continue;
            if (strcmp(argv[i], argv[j]) == 0) {
                isDuplicate = 1;
                break;
            }
        }

        if (isDuplicate) {
            argv[i] = NULL;
        }
        isDuplicate = 0;
    }
}

// Create an integer array
int *newIntArray(int size) {
    if (size <= 0) return NULL;
    int *newArray = calloc(size, sizeof(int));
    if (newArray == NULL) return NULL;
    return newArray;
}

// Create a double array
double *newDoubleArray(int size) {
    if (size <= 0) return NULL;
    double *newArray = calloc(size, sizeof(double));
    if (newArray == NULL) return NULL;
    return newArray;
}

// Get index from urlArray
int getIndexFromArray(int *urlArray, int url, int size) {
    if (urlArray == NULL || url < 0 || size <= 0) return -1;
    int i;
    for (i = 0; i < size; i++) {
        // Get its index
        if (urlArray[i] == url) return i;
    }
    return -1;
}

// Get top ten from resultArray
void getTopTen(double *resultArray, int *urlArray, int size) {
    if (resultArray == NULL || urlArray == NULL || size <= 0) return;

    // Loop ten times and get top ten
    int i, j, highestIndex = 0;
    double highest = 0;
    for (i = 0; i < 10; i++) {
        // Less than 10
        if (i >= size) break;
        // Get top ten
        for (j = i; j < size; j++) {
            // Find the highest
            if (resultArray[j] > highest) {
                highest = resultArray[j];
                highestIndex = j;
            }
        }
        // printf("Index: %d, value: %f\n", highestIndex, highest);
        if (highest == 0) break;
        // Swap value
        swapValue(resultArray, highestIndex, i);
        // Swap index
        swapIndex(urlArray, highestIndex, i);
        // reset highest
        highest = 0, highestIndex = 0;
    }
}

// Swap index for urlArray
void swapIndex(int *urlArray, int index1, int index2) {
    if (urlArray == NULL) return;

    int temp = urlArray[index1];
    urlArray[index1] = urlArray[index2];
    urlArray[index2] = temp;
}

// Swap value for urlArray
void swapValue(double *resultArray, int index1, int index2) {
    if (resultArray == NULL) return;

    double temp = resultArray[index1];
    resultArray[index1] = resultArray[index2];
    resultArray[index2] = temp;
}

// Calculate term frequency value for keyword in a url
double calTfValue(int count) {
    return (double)count;
}

// Calculate inverse document frequency value for collection
double calIdfValue(int contained, int total) {
    return (double)log10((double)total / (double)contained);
}

// Calculate term frequency–inverse document frequency for keyword
double calTfidfValue(double tf, double idf) {
    return tf * idf;
}

// How to use this program
void showUsage() {
    printf("Usage: ./searchTfIdf [keyword]\nThere should at least one keyword");
    exit(1);
}

// Fatal error
void fatalError(char *message) {
    if (message == NULL) exit(1);
    printf("%s\n", message);
    exit(1);
}

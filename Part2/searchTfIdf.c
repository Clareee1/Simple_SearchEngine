//
//  searchTfIdf.c
//  Created by Henry Quan on 20/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
// Fatal error
void fatalError(char *message);

int main(int argc, char *argv[]) {
    // There has to be at least one words
    if (argc <= 1) showUsage();

    // Get the number of keywords we have
    int keywordCount = getNumOfKeywordFromFile("invertedIndex.txt");
    // Well, too many keywords than we have
    if (argc - 1 > keywordCount) fatalError("Too many keywords");

    // Get the total number of urls we have in collection.txt for idf
    int totalUrlCount = getNumOfUrlFromFile("collection.txt");
    // Create a double array of size totalUrlCount to hold result
    double *resultArray = newDoubleArray(totalUrlCount);
    if (resultArray == NULL) fatalError("Out of memory");
    // Create another temp array with same size to hold temp url
    int *tempArray = newIntArray(totalUrlCount);
    if (tempArray == NULL) fatalError("Out of memory");


    // Store the index for all urls
    int *urlArray = getNameOfUrlFromFile("collection.txt", totalUrlCount);
    if (urlArray == NULL) fatalError("Out of memory");

    int i, j;
    for (i = 1; i < argc; i++) {
        strlower(argv[i]);
        // Repeat for each keyword
        int urlWithKeyword = getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[i], tempArray);
        double idf = calIdfValue(urlWithKeyword, totalUrlCount);
        for (j = 0; j < urlWithKeyword; j++) {
            // Repeat for each url
            char buffer[64]; // Store url full name
            sprintf(buffer, "url%d.txt", tempArray[j]);
            // Get term frequency
            int tf = getKeywordCountFromUrl(buffer, argv[i]);
            // Get index
            int index = getIndexFromArray(urlArray, tempArray[j], totalUrlCount);
            // Add this value to resultArray if valid
            if (index != -1) resultArray[index] += calTfidfValue(calTfValue(tf), idf);
        }
    }

    for (i = 0; i < totalUrlCount; i++) {
        // Display results
        printf("url%d, %.6f", urlArray[i], resultArray[i]);
    }

    free(urlArray);
    free(resultArray);

    return 0;
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

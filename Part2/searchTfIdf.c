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
// Swap index for urlArray
void swapIndex(int *urlArray, int index1, int index2);
// Swap value for urlArray
void swapValue(double *resultArray, int index1, int index2);
// Get top ten from resultArray
void getTopTen(double *resultArray, int *urlArray, int size);
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
        if (!hasKeyword("invertedIndex.txt", argv[i])) continue;
        // Repeat for each keyword
        int urlWithKeyword = getNumOfUrlForKeywordFromFile("invertedIndex.txt", argv[i]);
        getNameOfUrlForKeywordFromFile("invertedIndex.txt", argv[i], tempArray);
        double idf = calIdfValue(urlWithKeyword, totalUrlCount);
        // printf("c: %d, idf: %f\n", urlWithKeyword, idf);
        for (j = 0; j < urlWithKeyword; j++) {
            // Repeat for each url
            char buffer[64]; // Store url full name
            sprintf(buffer, "url%d.txt", tempArray[j]);
            // Get term frequency
            int tf = getKeywordCountFromUrl(buffer, argv[i]);
            // Get index
            int index = getIndexFromArray(urlArray, tempArray[j], totalUrlCount);
            // printf("tf: %d, index: %d, idtdf: %f\n", tf, index, calTfidfValue(calTfValue(tf), idf));
            // Add this value to resultArray if valid
            if (index != -1) resultArray[index] += calTfidfValue(calTfValue(tf), idf);
        }
    }

    // Free tempArray
    free(tempArray);

    // Sort resultArray
    getTopTen(resultArray, urlArray, totalUrlCount);
    for (i = 0; i < 10; i++) {
        if (i >= totalUrlCount) break;
        if (resultArray[i] == 0) break;
        printf("url%d, %0.6f\n", urlArray[i], resultArray[i]);
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

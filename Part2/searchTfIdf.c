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
// Fatal error
void fatalError(char *message);

int main(int argc, char *argv[]) {
    // There has to be at least one words
    if (argc <= 1) showUsage();

    // Get the number of keywords we have
    int keywordCount = getNumOfKeywordFromFile("invertedIndex.txt");
    // Well, too many keywords than we have
    if (argc - 1 > keywordCount) fatalError("Too many keywords");

    // Check if we have that word in invertedIndex.txt
    char **keywords = getKeywordFromFile("invertedIndex.txt", keywordCount);
    if (keywords == NULL) fatalError("Out of memory");

    int totalUrlCount = getNumOfUrlFromFile("collection.txt");
    printf("%d url%s\n", totalUrlCount, totalUrlCount <= 1 ? "" : "s");

    /*
        TODO
        I need to open each url and see if it contains that keywords
        At the same, I will count how many times it appears
        Loop ends

        Calculate idf times with td -> tdidf
        sort by tdidf
    */

    return 0;
}

// Calculate term frequency value for keyword in a url
double calTfValue(int count) {
    return (double)count;
}

// Calculate inverse document frequency value for collection
double calIdfValue(int contained, int total) {
    return log10(total / contained);
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

//
//  testUnit.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "parser.h"

// Everything passed, full mark. YEAH!!
void fullmark();
// Show fatal error and exit
void fatalError(char *error);
// Show that test passed
void testPassed(char *name);
// Test everything to get full mark
void testEverything();
// Test parser.c
void testParser();

int main(int argc, char *argv[]) {
    testEverything();
    return 0;
}

// Test everything to get full mark
void testEverything() {
    testParser();
    fullmark();
}

// Test parser.c
void testParser() {
    // Testing getNumOfUrlFromFile
    int t1 = getNumOfUrlFromFile("url/collection.txt");
    if (t1 != 7) fatalError("getNumOfUrlFromFile");
    else testPassed("getNumOfUrlFromFile");

    // Testing getNumFromString part1
    int t2 = getNumFromString("url888.txt");
    if (t2 != 888) fatalError("getNumFromString part 1");
    else testPassed("getNumFromString part 1");
    // Testing getNumFromString part2
    int t2_2 = getNumFromString("url888");
    if (t2_2 != 888) fatalError("getNumFromString part 2");
    else testPassed("getNumFromString part 2");
    // Testing getNumFromString part3
    int t2_3 = getNumFromString("url/url231.txt");
    if (t2_3 != 231) fatalError("getNumFromString part 3");
    else testPassed("getNumFromString part 3");

    // Testing getNameOfUrlFromFile
    int *t3 = getNameOfUrlFromFile("url/collection.txt", t1);
    if (t3 == NULL) fatalError("getNameOfUrlFromFile");
    else {
        int i;
        for (i = 0; i < t1; i++) {
            printf("url%d\n", t3[i]);
        }
        testPassed("getNameOfUrlFromFile");
    }

    // Testing getUrlTxtFromFile
    int *urlArray = calloc(t1, sizeof(int));
    if (urlArray == NULL) fatalError("Memory");

    int t4;
    for (t4 = 0; t4 < t1; t4++) {
        // Open all url txt
        char name[64];
        sprintf(name, "url/url%d.txt", t3[t4]);
        printf("url%d: \n", t3[t4]);
        // Check for url count
        int urlCount = getUrlFromFile(name, urlArray);
        printf("%d url%s in %s\n", urlCount, urlCount == 0 ? "" : "s", name);
        int i;
        for (i = 0; i < urlCount; i++) {
            if (urlArray[i] == 0) continue;
            printf("url%d\n", urlArray[i]);
            urlArray[i] = 0;
        }
        printf("\n\n");
    }
    testPassed("getUrlFromFile / getTxtFromFile");
}

// Show fatal error and exit
void fatalError(char *error) {
    printf("%s is incorrect\n", error);
    exit(1);
}

// Show that test passed
void testPassed(char *name) {
    printf("\"%s\" passed\n\n", name);
}

// Everything passed, full mark. YEAH!!
void fullmark() {
    printf("\nAll tests passed - Full Mark (100%%)\n");
}

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
    int t4;
    for (t4 = 0; t4 < t1; t4++) {
        // Open all url txt
        char name[64];
        sprintf(name, "url/url%d.txt", t3[t4]);
        printf("url%d: \n", t3[t4]);
        getUrlTxtFromFile(name);
    }
    testPassed("getUrlTxtFromFile");

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

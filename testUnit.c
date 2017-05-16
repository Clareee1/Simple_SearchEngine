//
//  testUnit.c
//  Created by Henry Quan on 05/15/17.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "parser.h"

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
}

// Test parser.c
void testParser() {
    // Testing getNumOfUrlFromFile
    int t1 = getNumOfUrlFromFile("url/collection.txt");
    if (t1 != 7) fatalError("getNumOfUrlFromFile is incorrect");
    else testPassed("getNumOfUrlFromFile");

    // Testing getNumFromString
    int t2 = getNumFromString("url1246.txt");
    if (t2 != 1246) fatalError("getNumFromString is incorrect");
    else testPassed("getNumFromString");

}

// Show fatal error and exit
void fatalError(char *error) {
    printf("%s\n", error);
    exit(1);
}

// Show that test passed
void testPassed(char *name) {
    printf("\"%s\" passed\n", name);
}

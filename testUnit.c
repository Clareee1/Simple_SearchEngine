//
//  testUnit.c
//  Created by Henry Quan on 05/15/17.
//

#include <stdio.h>
#include <assert.h>
#include "parser.h"

// Show fatal error and exit
void fatalError(char *error);
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
    int
}

// Show fatal error and exit
void fatalError(char *error) {
    printf("%s\n", error);
    exit(1);
}

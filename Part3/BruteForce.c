//
//  BruteForce.c
//  Created by Henry Quan on 29/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

// Show usage
void Usage();
// Fatal error
void fatalError(char *message);

int main(int argc, char *argv[]) {
    // Read all files
    if (argc < 2) Usage();
    else {
        // Create an new Array
        Array new = newList(argc - 1);
        if (new == NULL) fatalError("Out of memory");

        int i;
        for (i = 1; i < argc; i++) {
            // Add to Array
            addToList(new, argv[i]);
        }
        updateUnionlist(new);
        // Calculate scaled-footrule distance
        BruteForce(new);
        freeArray(new);
    }
    return 0;
}

// Show usage
void Usage() {
    printf("Usage: ./scaledFootrule [filename] ...\n");
    printf("There should be at least one file\n");
    exit(1);
}

// Fatal error
void fatalError(char *message) {
    if (message == NULL) exit(1);
    printf("%s\n", message);
    exit(1);
}

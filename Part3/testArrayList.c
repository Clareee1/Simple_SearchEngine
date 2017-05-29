#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int main(int argc, char *argv[]) {
    // Read all files
    if (argc < 2) printf("No input files\n");
    else {
        // Create an new Array
        Array new = newList(argc - 1);
        if (new == NULL) exit(1);
        // Add to Array
        int i;
        for (i = 1; i < argc; i++) {
            addToList(new, argv[i]);
        }
        updateUnionlist(new);
        printArray(new);
        freeArray(new);
    }
    return 0;
}

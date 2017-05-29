//
//  ArrayList.c
//  Created by Henry Quan on 29/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

typedef struct arrayList {
    // List with size
    int *list;
    int size;
    // Max value
    int max;
    // Next Prev pointers
    struct arrayList *next;
    struct arrayList *prev;
} *ArrayList;

struct arrayRep {
    int numOfArray;
    ArrayList first;
    ArrayList last;

    // For the union set
    int *unionList;
    int unionSize;

    // Max value in all arrays
    int max;
    // The sum of size for all array
    int totalSize;
};

static ArrayList newNode(char *name) {
    if (name == NULL) return NULL;

    // Setup newNode
    ArrayList new = malloc(sizeof(struct arrayList));
    if (new == NULL) return NULL;
    new -> size = new -> max = 0;
    new -> prev = new -> next = NULL;

    FILE *fp;
    // No such file was found
    if ((fp = fopen(name, "r")) == NULL) return NULL;

    // Get number of lines
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') new -> size++;
    }

    // Reset file pointer
    rewind(fp);
    // Setup list
    new -> list = calloc(new -> size, sizeof(int));
    if (new -> list == NULL) return NULL;
    int buffer = 0, index = 0;
    while ((fscanf(fp, " url%d ", &buffer)) == 1) {
        // Update max
        if (buffer > new -> max) new -> max = buffer;
        // Update list
        new -> list[index] = buffer;
        index++;
    }

    return new;
}

// Create a new array list with size
Array newList(int size) {
    if (size < 1) return NULL;

    // Malloc space for struct
    Array new = malloc(sizeof(struct arrayRep));
    if (new == NULL) return NULL;

    new -> numOfArray = new -> unionSize = new -> max = new -> totalSize = 0;
    new -> first = new -> last = NULL;
    new -> unionList = NULL;

    return new;
}

// Update unionList (really expensive)
void updateUnionlist(Array array) {
    if (array == NULL) return;
    // Malloc space for unionList
    int *tempList = calloc(array -> max, sizeof(int));
    if (tempList == NULL) return;

    // Loop through all list and get a union list
    int i;
    ArrayList curr;
    for (curr = array -> first; curr != NULL; curr = curr -> next) {
        for (i = 0; i < curr -> size; i++) {
            tempList[(curr -> list[i] - 1)]++;
        }
    }
    // Get size of unionList
    for (i = 0; i < array -> max; i++) {
        if (tempList[i] > 0) array -> unionSize++;
    }
    // Free old one
    if (array -> unionList != NULL) free(array -> unionList);
    // Update a new one
    array -> unionList = malloc((array -> unionSize) * sizeof(int));
    if (array -> unionList == NULL) return;
    int index = 0;
    for (i = 0; i < array -> max; i++) {
        if (tempList[i] > 0) {
            array -> unionList[index] = i + 1;
            index++;
        }
    }
}

// Add a new rank into arrayList
void addToList(Array array, char *name) {
    if (name == NULL) return;

    // Add it to list
    ArrayList newArray = newNode(name);
    if (newArray == NULL) return;

    if (array -> numOfArray <= 0) {
        // This is the first array
        array -> first = array -> last = newArray;
        // Its max is current max
        array -> max = newArray -> max;
    } else {
        // last -> new, last <- new
        array -> last -> next = newArray;
        newArray -> prev = array -> last;
        array -> last = newArray;
        if (newArray -> max > array -> max) {
            // Update max
            array -> max = newArray -> max;
        }
    }
    array -> totalSize += newArray -> size;
    array -> numOfArray++;
}

// Print an Array
void printArray(Array array) {
    if (array == NULL) return;

    // Start with basic stats
    int size = array -> numOfArray;
    printf("There %s %d array%s in this struct\n", size > 1 ? "are" : "is", size, size > 1 ? "" : "s");
    int i;
    for (i = 0; i < array -> unionSize; i++) {
        printf("%d %s ", array -> unionList[i], i == (array -> unionSize - 1) ? "" : "->");
    }
    printf("\nSize: %d Max: %d\n", array -> unionSize, array -> max);
    printf("Total size: %d\n\n", array -> totalSize);

    ArrayList curr;
    for (curr = array -> first; curr != NULL; curr = curr -> next) {
        for (i = 0; i < curr -> size; i++) {
            printf("%d %s ", curr -> list[i], i == (curr -> size - 1) ? "" : "->");
        }
        printf("\nSize: %d Max: %d\n", curr -> size, curr -> max);
    }
}

// Free an Array
void freeArray(Array array) {
    if (array == NULL) return;

    // Free all lists
    ArrayList curr;
    for (curr = array -> first; curr != NULL; curr = curr -> next) {
        free(curr -> list);
    }

    free(array -> unionList);
    free(array);
}

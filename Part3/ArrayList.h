//
//  ArrayList.h
//  Created by Henry Quan on 29/05/17.
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct arrayRep * Array;

// Create a new array list with size
Array newList(int);
// Update unionList
void updateUnionlist(Array);
// Add a new rank into arrayList
void addToList(Array, char *);
// Print an Array
void printArray(Array);
// Free an Array
void freeArray(Array);

#endif

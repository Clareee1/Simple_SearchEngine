// Tree.h ... interface to binary search tree ADT
// Written by John Shepherd, March 2013
// Modified by Aldhytha Karina Sari, 21/05/2017

#ifndef BSTREE_H
#define BSTREE_H

// client view of a Tree
typedef struct TreeRep *Tree;

// Interface Functions
// create an empty Tree
Tree newTree();
// free memory associated with Tree
void dropTree(Tree);
// display a Tree + stats about Tree
void showTree(FILE*, Tree);
// insert a new value into a Tree
void TreeInsert(Tree, char*);
// delete a value from a Tree
void TreeDelete(Tree, char*);
// check whether a value is in a Tree
void TreeFindAndInsert(Tree, char*, int);
// compute depth of Tree
int TreeDepth(Tree);
// count #nodes in Tree
int TreeNumNodes(Tree);

#endif

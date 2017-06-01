// Tree.h ... interface to binary search tree ADT
// Written by John Shepherd, March 2013
// Modified by Aldhytha Karina Sari, 21/05/2017
//
// Removed the following lines:
// kinds of insertion supported
// typedef enum {
// 	 InsertAtLeaf,
// 	 InsertAtRoot,
// 	 InsertRandom,
// 	 InsertRebalance,
// 	 InsertSplay,
// 	 InsertAVL
// } Style;
// Items and operations on Items
// typedef int Key;
// typedef Key Item; // item is just a key
// #define key(it) (it)
// #define cmp(k1,k2) ((k1) - (k2))
// #define less(k1,k2) (cmp(k1,k2) < 0)
// #define eq(k1,k2) (cmp(k1,k2) == 0)
//
// Removed the void TreeDelete(Tree, char *) function;
// Removed the int TreeNumNodes(Tree);
// Changed the TreeFind function (see BSTree.c)
// Changed all the item/key to a char * data type

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
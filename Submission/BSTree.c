// Tree.h ... implementation of binary search tree ADT
// Written by John Shepherd, March 2013
// Modified by Aldhytha Karina Sari, 21/05/2017
//
// Removed the following functions:
// -static void doShowTree(Link);
// -static Link insert(Link,Item);
// -static Link insertAtRoot(Link,Item);
// -static Link insertRandom(Link,Item);
// -static Link insertRebalance(Link,Item);
// -static Link searchSplay(Link,Key,int *);
// -static Link partition(Link,int);
// -static Link rebalance(Link);
// -void TreeDelete(Tree t, char* keyword);
// -static Link delete(Link t, char* keyword);
// -static Link deleteRoot(Link t);
// -int TreeNumNodes(Tree t);
//
// Added the following functions:
// -static void BSTreeInfix (FILE * fp, Link t);
// -static void showBSTreeNode(FILE * fp, Link t);
// -static int size(Link t);
//
// Changed the following functions:
// -void TreeFind(Tree, char*, int); to void TreeFindAndInsert(Tree t, char* keyword, int url);
// -static void drop(Link t);
// Changed all the item/key to a char * data type

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "IntList.h"

// Representation of Trees and Nodes

typedef struct Node *Link;

typedef struct Node {
	char* value;
	IntList urlList;
	Link left, right;
	Tree within;  // which tree contains this Node
} Node;

typedef struct TreeRep {
	Link root;
} TreeRep;

// Forward references for private functions

//static void doShowTree(Link);
static void drop(Link);
static int cmpValue (char* it2, Link t);
static void showBSTreeNode(FILE * fp, Link t);
static void BSTreeInfix (FILE * fp, Link t);
static Link InsertAVL(Link t, char* it);
static Link newNode(char*);
static Link search(Link,char*);
static Link delete(Link,char*);
static Link deleteRoot(Link);
static Link rotateL(Link);
static Link rotateR(Link);
static int depth(Link);
static int size(Link);

// used to hold current tree during insertion

Tree thisTree;

// Helper: make a new node containing a value
static Link newNode(char* v)
{
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = strdup(v);
	new->left = new->right = NULL;
	new->urlList = NULL;
	new->within = thisTree;
	return new;
}

// Interface: create a new empty Tree
Tree newTree()
{
	TreeRep *new = malloc(sizeof(TreeRep));
	assert(new != NULL);
	new->root = NULL;
	return new;
}

// Interface: free memory associated with Tree
void dropTree(Tree t)
{
	if (t == NULL) return;
	drop(t->root);
	free(t);
}

// Helper: recursive drop
static void drop(Link t)
{
	if (t == NULL) return;
	drop(t->left);
	drop(t->right);
	freeIntList(t->urlList);
	free(t->value);
	free(t);
}

// display BSTree root node
static void showBSTreeNode(FILE * fp, Link t)
{
	if (t == NULL) return;
	fprintf(fp, "%s ", t->value);
	showIntList(fp, t->urlList);
}

static void BSTreeInfix (FILE * fp, Link t)
{
	if (t == NULL) return;
	BSTreeInfix(fp, t->left);
	showBSTreeNode(fp, t);
	BSTreeInfix(fp, t->right);
}
// Interface: display a Tree
void showTree(FILE * fp, Tree t)
{
	BSTreeInfix (fp, t->root);
}

// Interface: depth of Tree (max path length)
int TreeDepth(Tree t)
{
	return depth(t->root);
}

// Helper: recursive depth calculation
static int depth(Link t)
{
	if (t == NULL) return 0;
	int ldepth = depth(t->left);
	int rdepth = depth(t->right);
	return 1 + ((ldepth > rdepth) ? ldepth : rdepth);
}

// Interface: count #nodes in Tree
int TreeNumNodes(Tree t)
{
	return size(t->root);
}

// Helper: recursive node counter
static int size(Link t)
{
	if (t == NULL) return 0;
	return 1 + size(t->left) + size(t->right);
}

// Interface: insert a new value into a Tree
// Interface: insert a new value into a Tree
void TreeInsert(Tree t, char* it)
{
	thisTree = t;
	t->root = InsertAVL(t->root, it);
}

static Link InsertAVL(Link t, char* it)
{
	if (t == NULL) {
		return newNode(it);
	}
	int diff = cmpValue(it, t);
	if (diff == 0)
		t->value = it;
	else if (diff < 0)
		t->left = InsertAVL(t->left, it);
	else if (diff > 0)
		t->right = InsertAVL(t->right, it);
	int dL = depth(t->left);
	int dR = depth(t->right);
	if ((dL - dR) > 1) t = rotateR(t);
	else if ((dR - dL) > 1) t = rotateL(t);
	//printf("After inserting %d, tree is:\n",key(it));
	//showTree(t);
	return t;
}

// Helpers: various styles of insert
static int cmpValue (char* keyword, Link t) {
   if (strcmp (keyword, t->value) == 0) {
      return 0;
   } else if (strcmp (keyword, t->value) < 0) {
      return -1;
   } else {
      return 1;
   }
}

// Interface: check whether a value is in a Tree
void TreeFindAndInsert(Tree t, char* keyword, int url)
{
	Link res;
	res = search(t->root, keyword);
	if (res == NULL) {
		TreeInsert(t, keyword);
		res = search(t->root, keyword);
		res->urlList = newIntList();
	}
	IntListInsert(res->urlList, url);
}

// Helpers: search functions to return Node containing key
static Link search(Link t, char* keyword)
{
	if (t == NULL) return NULL;
	Link res = NULL;
	int diff = cmpValue(keyword, t);
	if (diff == 0)
		res = t;
	else if (diff < 0)
		res = search(t->left, keyword);
	else if (diff > 0)
		res = search(t->right, keyword);
	return res;
}

// Interface: delete a value from a Tree
void TreeDelete(Tree t, char* keyword)
{
	t->root = delete(t->root, keyword);
}

// Helper: recursive delete
static Link delete(Link t, char* keyword)
{
	if (t == NULL) return NULL;
	int diff = cmpValue(keyword, t);
	if (diff == 0)
		t = deleteRoot(t);
	else if (diff < 0)
		t->left = delete(t->left, keyword);
	else if (diff > 0)
		t->right =  delete(t->right, keyword);
	return t;
}

// Helper: delete root of tree
static Link deleteRoot(Link t)
{
	Link newRoot;
	// if no subtrees, tree empty after delete
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	// if only right subtree, make it the new root
	else if (t->left == NULL && t->right != NULL) {
		newRoot = t->right;
		free(t);
		return newRoot;
	}
	// if only left subtree, make it the new root
	else if (t->left != NULL && t->right == NULL) {
		newRoot = t->left;
		free(t);
		return newRoot;
	}
	// else (t->left != NULL && t->right != NULL)
	// so has two subtrees
	// - find inorder successor (grab value)
	// - delete inorder successor node
	// - move its value to root
	Link succ = t->right; // not null!
	while (succ->left != NULL) {
		succ = succ->left;
	}
	char* succVal = strdup(succ->value);
	t = delete(t,succVal);
	t->value = strdup(succVal);
	return t;
}

// Helper: rotate tree right around root
Link rotateR(Link n1)
{
	if (n1 == NULL) return NULL;
	Link n2 = n1->left;
	if (n2 == NULL) return n1;
	n1->left = n2->right;
	n2->right = n1;
	return n2;
}

// Helper: rotate tree left around root
Link rotateL(Link n2)
{
	if (n2 == NULL) return NULL;
	Link n1 = n2->right;
	if (n1 == NULL) return n2;
	n2->right = n1->left;
	n1->left = n2;
	return n1;
}

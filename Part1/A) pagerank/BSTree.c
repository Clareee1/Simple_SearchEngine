// Tree.h ... implementation of binary search tree ADT
// Written by John Shepherd, March 2013
// Modified by Aldhytha Karina Sari, 21/05/2017

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
//static Link partition(Link, int);
//static Link rebalance(Link);
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
/*
// Helper: rebalance tree by moving median to root
static Link rebalance(Link t)
{
	if (t == NULL) return NULL;
    if (size(t) < 2) return t;
    // put node with median key at root
    t = partition(t, size(t)/2);
    // then rebalance each subtree
    t->left = rebalance(t->left);
    t->right = rebalance(t->right);
    return t;
}

static Link partition(Link t, int i)
{
   if (t == NULL) return NULL;
   assert(0 <= i && i < size(t));
   int n = size(t->left);
   if (i < n) {
      t->left = partition(t->left, i);
      t = rotateR(t);
   }
   if (i > n) {
      t->right = partition(t->right, i-n-1);
      t = rotateL(t);
   }
   return t;
}
*/
// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

// data structures
typedef struct asciinode_struct asciinode;
struct asciinode_struct
{
	asciinode * left, * right;
	//length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	//-1=I am left, 0=I am root, 1=I am right
	int parent_dir;
	//max supported unit32 in dec, 10 digits max
	char label[11];
};

/*
// functions
void print_level(asciinode *node, int x, int level);
void compute_edge_lengths(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
asciinode *build_ascii_tree(Link t);
void free_ascii_tree(asciinode *node);

#define MAX_HEIGHT 10000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

#define MIN(X,Y)  (((X) < (Y)) ? (X) : (Y))
#define MAX(X,Y)  (((X) > (Y)) ? (X) : (Y))

int gap = 3;  // gap between left and right nodes

//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;    

//prints ascii tree for given Tree structure
static void doShowTree(Link t)
{
	asciinode *proot;
	int xmin, i;
	if (t == NULL) return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		lprofile[i] = INFINITY;
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = MIN(xmin, lprofile[i]);
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT) {
		printf("(Tree is taller than %d; may be drawn incorrectly.)\n",
			MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

//This function prints the given level of the given tree, assuming
//that the node has the given x coordinate.
void print_level(asciinode *node, int x, int level)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++)
			printf(" ");
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
		  for (i=0; i<(x-print_next-(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf("/");
		  print_next++;
		}
		if (node->right != NULL)
		{
		  for (i=0; i<(x-print_next+(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf("\\");
		  print_next++;
		}
	}
	else
	{
		print_level(node->left,
			    x-node->edge_length-1,
			    level-node->edge_length-1);
		print_level(node->right,
			    x+node->edge_length+1,
			    level-node->edge_length-1);
	}
}


//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);
*/
	/* first fill in the edge_length of node */
/*	if (node->right == NULL && node->left == NULL)
		node->edge_length = 0;
	else
	{
		if (node->left == NULL)
			hmin = 0;
		else {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
				rprofile[i] = -INFINITY;
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		if (node->right == NULL)
			hmin = 0;
		else {
			for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
		    		lprofile[i] = INFINITY;
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		delta = 4;
		for (i=0; i<hmin; i++) {
			int w = gap+1+rprofile[i]-lprofile[i];
			delta = (delta > w) ? delta : w;
		}

		//If the node has two children of height 1, then we allow the
		//two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
		      (node->right != NULL && node->right->height == 1))
				&& delta > 4)
			delta--;
		node->edge_length = ((delta+1)/2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (node->left != NULL)
		h = MAX(node->left->height + node->edge_length + 1, h);
	if (node->right != NULL)
		h = MAX(node->right->height + node->edge_length + 1, h);
	node->height = h;
}

asciinode *build_ascii_tree_recursive(Link t)
{
	asciinode * node;

	if (t == NULL) return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	if (node->left != NULL) node->left->parent_dir = -1;
	if (node->right != NULL) node->right->parent_dir = 1;
	sprintf(node->label, "%s", t->value);
	node->lablen = strlen(node->label);;
	return node;
}


//Copy the tree into the ascii node structre
asciinode *build_ascii_tree(Link t)
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
	if (node == NULL) return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
	if (node->left != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
			lprofile[y+i] = MIN(lprofile[y+i], x-i);
	}
	compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
	if (node->right != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
	  		rprofile[y+i] = MAX(rprofile[y+i], x+i);
	}
	compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}
*/
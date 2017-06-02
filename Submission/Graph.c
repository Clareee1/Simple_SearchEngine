// Graph.c ... implementation of Graph ADT (COMP1927 week 7 Lab)
// Written by John Shepherd, May 2013
// Modified by Aldhytha Karina Sari (Alina) 01/06/2017
//
// Added the following functions:
// -double HamiltonPath(Graph, Vertex, double, int *, IntList, int *);
// Local:
// -int hasEdge (Graph, Vertex, Vertex);
// -void arrayIntCopy (int *, int *, int);
// -int HamiltonR(Graph, IntList, Vertex, double, int, double*, int *, int *, int *, int *);
//
// Removed the following functions:
// -int  findPath(Graph, Vertex, Vertex, int, int *);
// -void showGraph(Graph g, int *names);
// -Edge mkEdge(Graph g, Vertex v, Vertex w, int weight);
// -void removeEdge(Graph g, Vertex v, Vertex w);

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "list.h"

#define FALSE 0
#define TRUE 1

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

//--------------------------------------------------------------------------------------
//local functions
//recursive hamilton (dfs)
int HamiltonR(Graph, IntList, Vertex, double, int, double*, int *, int *, int *, int *);
//if the 2 vertices are connected by an edge
int hasEdge (Graph, Vertex, Vertex);
//copy array of integer and set
void locationCopy (int *, int *, int);
//--------------------------------------------------------------------------------------

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	int **edges = malloc (nV*sizeof(int*));
	assert (edges != NULL);
	int i,j;
	for (i = 0; i < nV; i++) {
		edges[i] = malloc (nV*sizeof(int));
		assert(edges[i] != NULL);
		for (j = i; j < nV; j++) {
			edges[i][j] = 0;
		}
	}
	Graph new = malloc (sizeof (GraphRep));
	assert (new != NULL);
	new->nV = nV;
	new->nE = 0;
	new->edges = edges;
	return new;
 }

// free memory associated with graph void dropGraph(Graph g)
void dropGraph (Graph g)
{
	assert(g != NULL);
	Vertex i;
	for (i = 0; i < g->nV; i++) {
		free (g->edges[i]);
	}
	free (g->edges);
	free (g);
}

// from Lecture (modified by Alina) - interface for hamilton path
double HamiltonPath(Graph g, Vertex src, double minDist, int * base, IntList L, int * location)
{
	//mallocked visited and tmpLocation arrays
	int * visited = calloc(g->nV, sizeof(int));
	int * tmpLocation = calloc (g->nV, sizeof(int));
	//temporary sum
	double sum = (double) 0;
	//set the last element to FALSE
	location[g->nV] = FALSE;
	//go to the recursive function
	HamiltonR(g, L, src, sum, 0, &minDist, visited, base, location, tmpLocation);
	//free the mallocked arrays
	free(visited);
	free(tmpLocation);
	//return the last element of location array
	return minDist;
}

// from Lecture (modified by Alina) - recursive hamilton (dfs)
int HamiltonR(Graph g, IntList L, Vertex v, double sum, int d, double * minDist, int * visited, int *base, int * location, int * tmpLocation)
{

	int t; 
	//set count to count how many vertices have been visited
	int count = 0;
	for (t = 0; t < g->nV; t++) count = count + visited[t];
	if (count == g->nV) return (d > g->nV - 1) ? 1 : 0;
	//visited vertex v
	visited[v] = 1;
	//take on the value of vertex v to index d (insert from the beginning of array)
	tmpLocation[d] = base[v];
	//tmpSum to calculate the distance from position v to position d
	double tmpSum = addition (v, d, g->nV, L);
	//check every vertex
	for (t = 0; t < g->nV; t++) {
		//if it has edges, hasn't been visited, and the sum doesn't exceed the current minimum distance
		if (!hasEdge(g,v,t)) continue;
		if (visited[t] == 1) continue;
		if (sum + tmpSum > *minDist) continue;
		//add the tmpSum to sum
		sum = sum + tmpSum;
		//the recursion :)
		if (HamiltonR(g, L, t, sum, d+1, minDist, visited, base, location, tmpLocation)) return 1;
		//reduce the sum by tmpSum so that the original sum is retained for the next element in the loop
		sum = sum - tmpSum;
	}
	//if all vertices are visited & the sum + tmpSum is less than the minDist
	if (count == g->nV-1 && sum + tmpSum < *minDist) {
		//set the minimum distance to sum+tmpSum
		*minDist = sum + tmpSum;
		//copy the minimum location to location array
		locationCopy (location, tmpLocation, g->nV);
		//set the last element to TRUE
		location[g->nV] = TRUE;
	}
	//reset the tmpLocation and visited to 0
	tmpLocation[d] = 0;
	visited[v] = 0;
	return 0;
}

//if the 2 vertices are connected by an edge
int hasEdge (Graph g, Vertex v, Vertex w) {
	if (validV(g, v) != 0 && validV(g, w) != 0 && g->edges[v][w] != 0 && g->edges[w][v] != 0) return 1;
	return 0;
}

//copy array of integer and set
void locationCopy (int * result, int * input, int size) {
	int i;
	for (i = 0; i < size; i++) result[i] = input[i];
}
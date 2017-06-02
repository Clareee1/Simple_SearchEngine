// Graph.h ... interface to Graph ADT (COMP1927 Lab Week 7)
// Written by John Shepherd, March 2013
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

#ifndef GRAPH1_H
#define GRAPH1_H

#include <stdio.h>
#include "list.h"

typedef struct GraphRep *Graph;

// vertices denoted by integers 0..N-1
typedef int Vertex;
// validity check
int validV(Graph,Vertex); 
// connect two vertices
void insertEdge(Graph, Vertex, Vertex, int);
// create new graph
Graph newGraph(int);
// free memory allocated for graph
void dropGraph(Graph);
//void showGraph(Graph, int*);
double HamiltonPath(Graph, Vertex, double, int *, IntList, int *);

#endif

// Graph2.c
// Modified version of Graph.c

#define MAXLENGTH 200

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "parser.h"

//A node
typedef struct  vNode *vlist;
struct vNode {
    int numLinksToIt;     //Stores number of links to url
    int numLinksOut;      //Stores number of links that url goes to
    int* linksToIt;   //An array of links that goes to url
};

//The Graph...
typedef struct GraphRep {
    int   nV;             //Number of urls altogether
    int*  indexArray;     //An array that stores the urls
    int**  edges;         //An actual graph, int[i][j] means i links to j
    vlist* lledges;       //List of nodes
} GraphRep;

//void makevList(int url, Graph g);
void addTovList(vlist node, int from, int to);

Graph createNewGraph(){

    //Obtain number of urls
    int size = getNumOfUrlFromFile("collection.txt");

	if (size == 0){ //if there are no links in collection
		return NULL;
	}

    //Obtains all urls and stores into Array
    int *index = getNameOfUrlFromFile("collection.txt", size);

    //Make space for graph
  	Graph new = malloc(sizeof(GraphRep));
  	assert(new != NULL);

    //Initialise Stuff
  	int i, j;
  	new->nV = size;
  	new->indexArray = index;

    //Make space for edges (the actual graph)
  	new->edges = malloc((size) * sizeof(int *));
  	assert(new->edges != NULL);

    //Initialise graph
  	for (i = 0; i < size; i++) {
  		  new->edges[i] = malloc((size) * sizeof(int));
  		  assert(new->edges[i] != NULL);
  		  for (j = 0; j < size; j++){
  			    new->edges[i][j] = 0;
        }
  	}

    //The annoying node
    vlist *e = malloc(size * sizeof(struct vNode));
    assert(e != NULL);
    new -> lledges = e;

    //Initialising node
    for (i = 0; i < size; i++) {
        new -> lledges[i] = malloc(sizeof(struct vNode));
        new -> lledges[i] -> linksToIt = (int*)calloc(size, sizeof(int));
        new -> lledges[i] -> linksToIt[0] = -1;
        new -> lledges[i] -> numLinksToIt = 0;
        new -> lledges[i] -> numLinksOut = 0;
    }

    //More initialising...
    char url[20];
    int tsize;
    int tarray[size];
    int k = 0;

    //Making and putting stuff into the graph
    for(i = 0; i < size; i++){
        //Gets url, its size and links
        sprintf(url, "url%d.txt", new -> indexArray[i]);
        tsize = getUrlFromFile(url, tarray);
        new -> lledges[i] -> numLinksOut = tsize;

        //Adds edge, and adds to node...
        k = 0;
        if(tsize != 0){
            for(j = 0; j < tsize; j++){
                k = findIndex(new, tarray[j], new -> nV);
                if (k > -1){
                    new->edges[i][k] = 1;   // i links to k
                    addTovList(new->lledges[k], i, size);
                }
            }
        }
    }
    //showGraph(new);
  	return new;

}

//Gets url given index
int urlGivenIndex(int index, Graph g){
    return g->indexArray[index];
}

//Free all space
void disposeGraph(Graph g)
{
	  if (g == NULL) return;
  	int i;
  	for (i = 0; i < g->nV; i++) {
  		free(g->edges[i]);
      free(g->lledges[i]->linksToIt);
    }
    free(g->indexArray);
  	free(g->edges);
    free(g->lledges);
    free(g);
}

//Returns number of urls in graph
int nVertices(Graph g){
    return g->nV;
}

//Returns the index value for url
int findIndex(Graph g, int value, int size){
    int i = 0;
    while(i < size){
        if(g -> indexArray[i] == value){
          return i;
        }
        i++;
    }
    return -1;
}

//Prints the graph
void showGraph(Graph g){
    int i = 0;
    int j = 0;
    for (i = 0; i < g->nV; i++){
        for(j = 0; j < g->nV; j++){
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}

//Copies into array the urls that link to url
void linkedToGiven(Graph g, int url, int* array){
    int i = 0;
    while(g->lledges[url]->linksToIt[i] != -1){
        array[i] = g->lledges[url]->linksToIt[i];
        i++;
    }
    array[i] = -1;
}

//Number of urls that links to given url
int numberOfLinksTo(Graph g, int url){
    return g -> lledges[url] -> numLinksToIt;
}

//Number of urls that url links to
int numberOfLinksOut(Graph g, int url){
    return g -> lledges[url] -> numLinksOut;
}


//Add index to the node...
void addTovList(vlist node, int from, int size){
    int i = 0;
    while(node -> linksToIt[i] != -1 && i < size){
        i++;
    }
    node -> linksToIt[i] = from;
    node -> numLinksToIt++;
    node -> linksToIt[i+1] = -1;
}

//If empty, returns 0, else 1.
int isGraphEmpty(Graph g){
    if(g == NULL || g->nV == 0){
        return 0;
    } else {
        return 1;
    }
}

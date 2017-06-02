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
int removeDuplicate(int* Array, int size, int curr);

Graph createNewGraph(){

    //Obtain number of urls
    int size = getNumOfUrlFromFile("collection.txt");

    if (size == 0){ //if there are no links in collection
        exit(1);
    }

    //Obtains all urls and stores into Array (index of array corresponds to url)
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
	assert(new -> lledges[i] -> linksToIt != NULL);
        new -> lledges[i] -> linksToIt[0] = -1;
        new -> lledges[i] -> numLinksToIt = 0;
        new -> lledges[i] -> numLinksOut = 0;
    }

    //More initialising...
    char url[20];
    int tsize;
    int k = 0;
    int dupli = 0;

    //Making and putting stuff into the graph
    for(i = 0; i < size; i++){   //scanning url with index i
        //Gets url, its size and links
        sprintf(url, "url%d.txt", new -> indexArray[i]);
        tsize = getNumUrlFromFile(url);
        if(tsize != 0){  //only if there are any urls in file
            int *tarray = malloc(sizeof(int) * (tsize+2)); //temporary array
            assert(tarray != NULL);
            getUrlFromFile(url, tarray);  //gets urls in the file
            dupli = removeDuplicate(tarray, tsize, new->indexArray[i]);
            tsize = tsize - dupli;
            new -> lledges[i] -> numLinksOut = tsize;

        //Adds edge, and adds to node...
            k = 0;
            for(j = 0; j < tsize; j++){
                k = findIndex(new, tarray[j], new -> nV);   //finds the index of url found in file
                if (k > -1 && k != i){    //adds to graph
                    new->edges[i][k] = 1;   // i links to k
                    addTovList(new->lledges[k], i, size);  //adds i to array containing
		    //urls that link to k 
                }
            }
            free(tarray);
        } else if (tsize == 0){    //else only update size
            new -> lledges[i] -> numLinksOut = tsize;
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
        free(g->lledges[i]);
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


//Add url to the node...
void addTovList(vlist node, int from, int size){
    int i = 0;
    while(node -> linksToIt[i] != -1 && i < size){
        i++;
    }
    node -> linksToIt[i] = from;
    node -> numLinksToIt++;
    node -> linksToIt[i+1] = -1;  // indicates where the values (urls) stops
}


//Removes repeated urls and urls that self loop (urls that link to itself)
int removeDuplicate(int* Array, int size, int curr){
    int* temp = Array;   //to compare with
    int count = 0;   //counts number of self loops and duplicates
    int i = 0;
    int j = 0;

    while(i < size){  //scans through array
        j = i + 1;
        while (j < size){    //compares each value to every value after it
            if(temp[i] == Array[j] || Array[j-1] == curr || Array[j] == curr){
                int k;
                if(Array[j-1] == curr){  //for self loop
                    k = j-1;
                } else {
                    k = j;
                }
                count++;
                //printf("array is %d and curr is %d\n", Array[j], curr);
                if(k != size){   //k is the index of the value we want to get rid of
                   while(k <= size){   //remove k by shifting everything forward.
                       Array[k] = Array[k+1];
                       k++;
                    }
                }
                if(i != 0){  //to not miss any duplicates (for repeated dups)
                    i--;
                }
                j--;  //for repeated dups
                size--;  //for repeated dups
            }
            j++;
        }
        i++;
    }
    return count;
}


// Graph2.c
// Modified version of Graph.c
//fix dispose funtion
//finish lledges...
#define MAXLENGTH 200

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "parser.h"


//DONE
typedef struct  vNode *vlist;
struct vNode {
    int numLinksToIt;
    int numLinksOut;
    int* linksToIt;
};


//DONE
typedef struct GraphRep {
    int   nV;
    int*  indexArray;
    int**  edges;
    vlist* lledges;
} GraphRep;

//void makevList(int url, Graph g);
void addTovList(vlist node, int from, int to);


//DONE
Graph createNewGraph(){

  	Graph new = malloc(sizeof(GraphRep));
  	assert(new != NULL);
    //printf("malloced space for graph\n");

    int size = getNumOfUrlFromFile("collection.txt");
    //printf("Got size, size is %d\n", size);
    int *index = getNameOfUrlFromFile("collection.txt", size);
    //printf("got indexs, first index is %d\n", index[0]);

  	int i, j;
  	new->nV = size;
    //printf("size is stored and newsize is %d\n", new -> nV);

  	new->indexArray = index;
    //printf("Index array is created, second one is %d\n", new -> indexArray[1]);


  	new->edges = malloc((size) * sizeof(int *));
  	assert(new->edges != NULL);
    printf("edges malloced\n");

  	for (i = 0; i < size; i++) {
  		new->edges[i] = malloc((size) * sizeof(int));
  		assert(new->edges[i] != NULL);
  		for (j = 0; j < size; j++){
  			new->edges[i][j] = 0;
        }
        //printf("edge %d malloced\n", i);
  	}

    vlist *e = malloc(size * sizeof(struct vNode));
    assert(e != NULL);
    //e[0] -> numLinks = 0;

    //printf("e malloced\n");

    new -> lledges = e;

    for (i = 0; i < size; i++) {
        new -> lledges[i] = malloc(sizeof(struct vNode));
        new -> lledges[i] -> linksToIt = (int*)calloc(size, sizeof(int));
        new -> lledges[i] -> linksToIt[0] = -1;
        new -> lledges[i] -> numLinksToIt = 0;
        new -> lledges[i] -> numLinksOut = 0;
        //printf("%d\n", new -> lledges[i] -> linksToIt[0]);
        //printf("e malloced completely\n");
    }

    char url[10];
    int tsize;
    int tarray[size];
    int k = 0;
    //printf("still fine\n");
    for(i = 0; i < size; i++){
        sprintf(url, "url%d.txt", index[i]);
        //printf("not fine\n");
        //tarray[0] = 1;
        tsize = getUrlFromFile(url, tarray);
        new -> lledges[i] -> numLinksOut = tsize;
        k = 0;
        //printf("linked to %d: ", i);

        while(k < 5){
            printf("%d ", tarray[k]);
            k++;
        }
        printf("\n");

        //tsize = getNumOfUrlFromFile(url);
        //printf("Number of links to %d is %d\n", i, tsize);
        //tarray = getNameOfUrlFromFile(url, tsize);
        //printf("temporary array is %d\n", tarray[0]);
        for(j = 0; j < tsize; j++){
            k = findIndex(new, tarray[j], new -> nV);
            //printf("k is %d\n", k);
            if (k != -1){
                new->edges[i][k] = 1;   // i links to k
            //printf("adding edge is fine, and k is %d\n", k);
                addTovList(new->lledges[k], i, size);
            }
            //printf("add to list is not fine, added %d to lledges\n", new -> lledges[k]);
        }
    }

    i = 0;
    j = 0;
    //printf("size is %d\n", size);
    for(i = 0; i < size; i++){
        //printf("%d is llinked to: ", i);
        j = 0;
        while(j < 8){
            printf("%d ", new->lledges[j]->linksToIt[j]);
            j++;
        }
    }
/*
    int q = 0;
    for (i = 0; i < size; i++){
        printf("%d is linked to: ",i);
        while(new -> lledges[i] -> linksToIt[q] != -1){
            printf("%d ", new->lledges[i] -> linksToIt[q]);
            q++;
        }
        printf("\n");
    }
   */

    showGraph(new);
  	return new;
}

int urlGivenIndex(int index, Graph g){

    return g->indexArray[index];


}

//not Done
void disposeGraph(Graph g)
{
	  if (g == NULL) return;
  	int i;
  	for (i = 0; i < g->nV; i++) {
  		free(g->edges[i]);
      free(g->lledges[i]->linksToIt);
      //free(g->lledges[i]);
    }
    free(g->indexArray);
  	free(g->edges);
    free(g->lledges);
    free(g);
}

//Done
int nVertices(Graph g){
    return g->nV;
}

//Done
int findIndex(Graph g, int value, int size){
    int i = 0;
    //printf("trying to find %d\n", value);

    while(i < size){
        if(g -> indexArray[i] == value){
          return i;
        }
        i++;
        //printf("i is %d and url is %d\n", g->indexArray[i], i);
    }
    return -1;
}



//Done
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

//Done
void linkedToGiven(Graph g, int url, int* array){
    int i = 0;
    //printf("url is %d\n", url);
    while(g->lledges[url]->linksToIt[i] != -1){
        //printf("Entered while for linked to given & %d\n", g->lledges[url]->linksToIt[i]);
        array[i] = g->lledges[url]->linksToIt[i];
        //printf("i is %d\n", i);
        i++;
    }
    array[i] = -1;
}

//Done
//Gets the number of links that links to given url
int numberOfLinksTo(Graph g, int url){
    //printf("NUmber of links to %d is %d\n", url, g->lledges[url] -> numLinks);

    return g -> lledges[url] -> numLinksToIt;
}

int numberOfLinksOut(Graph g, int url){
   return g -> lledges[url] -> numLinksOut;
}



void addTovList(vlist node, int from, int size){
    int i = 0;
    while(node -> linksToIt[i] > -1 && i < size){
        i++;
    }
    //printf("entered add to list function\n");
    node -> linksToIt[i] = from;
    node -> numLinksToIt++;
    printf("entered add to vlist\n");
    node -> linksToIt[i+1] = -1;
}

int isGraphEmpty(Graph g){
    if(g == NULL || g->nV == 0){
        return 0;
    } else {
        return 1;
    }

}

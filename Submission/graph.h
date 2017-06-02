//graph2.h
//I  included comments  for the sake of my teammates >_<

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

//Creates a new graph with links included and many other things
Graph createNewGraph();

//Hopefully frees all memory associated with the graph
void  disposeGraph(Graph g);

//Finds the total number of urls
int nVertices(Graph g);

//Finds the index given url
int findIndex(Graph g, int value, int size);

//prints the graph
void showGraph(Graph g);

//stores the indexs of the urls that links to given url
// ends with -1
void linkedToGiven(Graph g, int url, int* array);

//Gets the number of links that link to given url
int numberOfLinksTo(Graph g, int url);


//Finds url given index
int urlGivenIndex(int index, Graph g);

//Number of links out of url
int numberOfLinksOut(Graph g, int url);

#endif

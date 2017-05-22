//Pagerank for Assignment 2 COMP1927 S1 2017
//By Hui Min Wang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph2.h"
#include "parser.h"

void initialiseArray(double* array, int size);
double abs2(double num);
void sortArray(double* PRarray, int size, int* array);
void printPRFunction(double* PRarray, Graph g, int size, int* sortedArray);
void pagerank(double d, double diffPR, int maxIterations);

int main(int argc, char * argv[]){

    if( argc == 4 ){
        double d = 0; 
        double diffPR = 0;
        int maxIter = 0;
        //Get stuff
        sscanf(argv[1], "%lf", &d); 
        sscanf(argv[2], "%lf", &diffPR);
        sscanf(argv[3], "%d", &maxIter);
        //Put into function 
        pagerank(d, diffPR, maxIter);
    }
    return 0;

}

void pagerank(double d, double diffPR, int maxIterations){
//A hell amount of initialising
    double d2  = d;
    Graph g = createNewGraph();
    int size = nVertices(g);  //Basically number of URLs
    int p = 0;
    int i, j;
    int tempArray[size];
    int linksIn = 0;  //number of links to url
    int linksFrom = 0;  //number of links from url
    double diff = diffPR;
    double PR = 0;
    double sum = 0;
    double currPRArray[size]; //current pagerank
    double prevPRArray[size]; //previous pagerank 
    initialiseArray(prevPRArray, size); //put 1/size for each

    if(isGraphEmpty(g) == 0){
        exit(0);
    }

//The math part
    while(p < maxIterations && diff >= diffPR){
        diff = 0;
        for (i = 0; i < size; i++){   // i is pi
            linkedToGiven(g, i, tempArray);  //an array of urls that link to i
            linksIn = numberOfLinksTo(g, i);  //number of links to i
            for (j = 0 ; j < linksIn; j++){   // j is pj
                linksFrom = numberOfLinksOut(g,tempArray[j]);  //get how many links go out of j
                sum = sum + prevPRArray[tempArray[j]]/linksFrom; 
            }
            assert(sum < 1);
            //Get PageRank!!! Finally!!!
            PR = (double)  (1-d2)/size *1.0000+ (double) d2*1.00000000*sum; 
            currPRArray[i] = PR;  //update currArray
            sum = 0;
        }

        //prev pagerank is now current pagerank
        for (j = 0; j < size; j++){
           diff = diff + abs2(prevPRArray[j] - currPRArray[j]);
           prevPRArray[j] = currPRArray[j];
        }
    }

    //initialise sorted array
    int sorted[size];
    for (i = 0; i < size; i++){
        sorted[i] = i;
    }

    sortArray(currPRArray, size, sorted);
    printPRFunction(currPRArray, g, size, sorted);
    disposeGraph(g);
}

void initialiseArray(double* array, int size){
    int i;
    double nsize = (double) size;
    for (i = 0; i < size; i++){
        array[i] = (1/nsize) * 1.00000000;
    }
    printf("array[0] is %.8f\n", array[0]); 
}

double abs2(double num){
    double ret = 0;
    if (num >= 0){
        ret = num;
    } else if (num < 0){
        ret = num*(-1);
    }
    return ret;
}

//Not Done
void sortArray(double* PRarray, int size, int* array){
    //some sort function
    //hopefully quicksort
}

//Print function
void printPRFunction(double* PRarray, Graph g, int size, int* sortedArray){
    int i;
    int url = 0;
    for (i = 0; i < size; i++){
        url = urlGivenIndex(sortedArray[i], g);
        printf("url");
        printf("%d, ", url);
        printf("%d, ", numberOfLinksTo(g, sortedArray[i]));
        printf("%.8f\n", PRarray[sortedArray[i]]);
    }
}


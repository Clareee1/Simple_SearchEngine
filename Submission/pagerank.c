//Pagerank for Assignment 2 COMP1927 S1 2017
//Finalising on 5/28/2017
//Use to calculate Pagerank for a group of urls
//Group Dragons001: Hui Min Wang, Alina, Henry


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "parser.h"

void initialiseArray(double* array, int size);
double abs2(double num);
void merge(int* array, int lo, int mid, int hi, double* PRarray);
void mergesort(int* array, int lo, int hi, double* PRarray);
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
    double d2  = d;      //in case g overwrites d
    Graph g = createNewGraph();
    int size = nVertices(g);  //Basically number of URLs
    int p = 0;
    int i, j;
    int tempArray[size];
    int linksIn = 0;  //number of links to url
    int linksFrom = 0;  //number of links from url
    double diff = diffPR;
    double PR = 0;		//To store pagerank before putting into array
    double sum = 0;		//Sum part of the pagerank formula
    double currPRArray[size]; //current pagerank
    double prevPRArray[size]; //previous pagerank
    initialiseArray(prevPRArray, size); //put 1/size for each

    if(g == NULL){
        exit(1);
    }

//The math part (NOTE: urls each have an allocated index, which you can find using indexArray in graph)
    while(p < maxIterations && diff >= diffPR){
        diff = 0;
        for (i = 0; i < size; i++){			//i is pi
            linkedToGiven(g, i, tempArray);		//an array of index of urls that link to i
            linksIn = numberOfLinksTo(g, i);	        //number of links to i
            for (j = 0 ; j < linksIn; j++){		// j is pj
                linksFrom = numberOfLinksOut(g,tempArray[j]);       //get how many links go out of j
		if( linksFrom != 0 && tempArray[j] != i ){	    //add if not 0 or selfloop
		    sum = sum + prevPRArray[tempArray[j]]/linksFrom;   //The sum part of the formula
		    //pagerank of url connecting to i/links coming out of that url
		}
            }
            assert(sum < 1);
            //Get PageRank!!! Finally!!!
            PR = (double)  (1-d2)/size *1.0000000+ (double) d2*1.00000000*sum;
            currPRArray[i] = PR;  //update currArray
            sum = 0;
        }

        //prev pagerank is now current pagerank
        for (j = 0; j < size; j++){
           diff = diff + abs2(prevPRArray[j] - currPRArray[j]);
           prevPRArray[j] = currPRArray[j];
        }
    }

    //initialise sorted array [1, 2, 3...]
    int sorted[size];
    for (i = 0; i < size; i++){
        sorted[i] = i;
    }

    //Sort PR
    mergesort(sorted, 0, size-1, currPRArray);
    //Print PR in file
    printPRFunction(currPRArray, g, size, sorted);
    //Free allocated memory
    disposeGraph(g);
}

//Used to store 1/size into every entry in array
void initialiseArray(double* array, int size){
    int i;
    double nsize = (double) size;
    for (i = 0; i < size; i++){
        array[i] = (1/nsize) * 1.00000000;
    }
}

//Finding absolute value of the number
double abs2(double num){
    double ret = 0;
    if (num >= 0){
        ret = num;
    } else if (num < 0){
        ret = num*(-1);
    }
    return ret;
}

//modified mergesort code from lectures
//only difference is it moves the index array as well
//to keep track of which url corresponds to what pagerank
void mergesort(int* array, int lo, int hi, double* PRarray){

    if(hi <= lo) return;
    int mid = (lo + hi)/2;
    mergesort(array, lo, mid, PRarray);
    mergesort(array, mid+1, hi, PRarray);
    merge(array, lo, mid, hi, PRarray);

}

void merge(int* array, int lo, int mid, int hi, double* PRarray){

    int i, j, k, nitems = hi-lo+1;
    double* tmp = malloc(nitems*sizeof(double));
    int* tmp2 = malloc(nitems*sizeof(int));

    i = lo; j = mid + 1; k = 0;
    while( i <= mid && j <= hi){
        if(PRarray[i] > PRarray[j]){
            tmp[k] = PRarray[i]*1.00000;
            tmp2[k] = array[i];
            k++;
            i++;
        } else {
            tmp[k] = PRarray[j] * 1.00000;
            tmp2[k] = array[j];
            k++;
            j++;
        }

    }

    while (i <= mid){
        tmp[k] = PRarray[i];
        tmp2[k] = array[i];
        i++;
        k++;

    }

    while (j <= hi){
        tmp[k] = PRarray[j];
        tmp2[k] = array[j];
        k++;
        j++;
    }

    for(i = lo, k = 0; i <= hi; i++, k++){
        array[i] = tmp2[k];
        PRarray[i] = tmp[k];
    }
    free(tmp2);
    free(tmp);
}

//Print function
void printPRFunction(double* PRarray, Graph g, int size, int* sortedArray){
    int i;
    int url = 0;
    FILE *fp;
    fp = fopen("pagerankList.txt", "w");
    for (i = 0; i < size; i++){ //prints url and PR
        url = urlGivenIndex(sortedArray[i], g);  //sortedArray contains index of url
        fprintf(fp, "url%d, %d, ", url, numberOfLinksOut(g, sortedArray[i]));
        fprintf(fp, "%.7f\n", PRarray[i]);   //PR array conatins PR
    }
    fclose(fp);
}

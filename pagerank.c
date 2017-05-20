//Pagerank for Assignment 2 COMP1927 S1 2017
//By Hui Min Wang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        sscanf(argv[1], "%lf", &d);
        sscanf(argv[2], "%lf", &diffPR);
        sscanf(argv[3], "%d", &maxIter);
        //scanf("%lf %lf %d", &d, &diffPR, &maxIter);
        printf("You have given %lf %lf %d\n", d, diffPR, maxIter);
        pagerank(d, diffPR, maxIter);
    }

    return 0;

}

void pagerank(double d, double diffPR, int maxIterations){

//A hell amount of initialising
    Graph g = createNewGraph();
    printf("Graph created\n");
    
    int size = nVertices(g);  //Basically number of URLs
    int p = 0;
    int i, j;
    int tempArray[size];
    int links;
    double diff = diffPR;
    double PR = 0;
    double sum = 0;
    double currPRArray[size];
    double prevPRArray[size];

    //printf("size is %d\n", size);

    initialiseArray(prevPRArray, size);
    //printf("initialise successful & is %.6lf\n", prevPRArray[0]);

    if(isGraphEmpty(g) == 0){
        exit(0);
    }
    printf("graph is not empty\n");

//The math part
    while(p < maxIterations && diff >= diffPR){
        //printf("Entered math while loop\n");
        diff = 0;
        for (i = 0; i < size; i++){   // i is pi
            linkedToGiven(g, i, tempArray);  // contains numbers linked to i
            int m = 0;
            printf("Scanning links to %d: ", i);
            while(m < 10){
                printf("%d ", tempArray[m]);
                m++;

            }
            printf("\n");
            //printf("successful in obtaining indexs %d\n", tempArray[0]);
            links = numberOfLinksTo(g, i);
            //printf("Number of links to %d is %d\n", i, links); 
            //printf("links is %d\n", links);
            int links2 = 0;
            for (j = 0 ; j < links; j++){   // j is pj
                links2 = numberOfLinksOut(g,j);
                sum = sum + prevPRArray[tempArray[j]]/links2;
                printf("sum is %.7f\n", sum);
            }


            printf("size is %d and links is %d\n ", size, links);
            double dsize = (double) size;
            //double dlinks = (double) links;

            PR = (double)  (1-d)/dsize * 1.00000000;
            printf("PR is %.6f\n", PR);
            PR = (double)  PR + (double) d*1.000000*sum;

            printf("PR is %.9f\n", PR);
            currPRArray[i] = PR;  //update currArray
            sum = 0;
        }


        for (j = 0; j < size; j++){
           diff = diff + abs2(prevPRArray[j] - currPRArray[j]);
           prevPRArray[j] = currPRArray[j];
        }
        printf("diff is %.6f\n", diff);
    }


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
        array[i] = (1/nsize) * 1.00000;
        //printf("size is %d\n", size);
        printf("array 1 is %.6f\n", array[i]);
    }
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

/*
int partition(Iten a[], int lo, int hi){

    int v = a[lo];
    int i = lo+1
    int j = hi;
    for(;;){
        while(less(a[i],v) && i < j){
            i++;
        }
        while(less(v, a[j]) && j < i){
            j--;
        }
        if(i == j) break;
        swap(a,i,j);
    }
    j = less(a[i], v) ? i : i-1;
    swap(a, lo, j);
    return j;

}

void medianOfThree(Item a[], int lo, int hi){
    int mid = (lo+hi)/2;
    if(less(a[mid], a[lo])) swap(a, lo, mid);
    if(less(a[hi], a[mid])) swap(a, mid, hi);
    if(less(a[mid], a[lo])) swap(a, lo, mid);
    swap(a, mid, lo+1);

}

void quicksort(int a[], int lo, int hi){
    int i;



}
*/


//Print function
void printPRFunction(double* PRarray, Graph g, int size, int* sortedArray){
    int i;
    int url = 0;
    for (i = 0; i < size; i++){
        url = urlGivenIndex(sortedArray[i], g);
        printf("url");
        printf("%d, ", url);
        printf("%d, ", numberOfLinksTo(g, sortedArray[i]));
        printf("%.7f\n", PRarray[sortedArray[i]]);
    }
}

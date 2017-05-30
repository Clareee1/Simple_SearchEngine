// inverted.c
// Written by Aldhytha Karina Sari (Alina), 21 May 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "BSTree.h"

int main (int argc, char * argv[]) {
	//if the input is correct
	if (argc == 1) {
		//create an array of all url from collection.txt
		int numUrl = getNumOfUrlFromFile ("collection.txt");
		int * urlArray = getNameOfUrlFromFile ("collection.txt", numUrl);
		//create a new tree called bst
		Tree bst = newTree();
		//for each url
		int i;
		for (i = 0; i < numUrl; i++) {
			//convert 21 into url21
 			char * tmp = getStringFromNum (urlArray[i]);
 			//convert url21 to url21.txt
 			tmp = strcat (tmp, ".txt");
 			//insert all the text in tmp file to the tree
			getTxtFromFile (tmp, bst);
			//free the temporary string
			free (tmp);
		}
		//open an invertedIndex.txt file (or make a new file if it doesn't exist)
		FILE *fp = fopen ("invertedIndex.txt", "w");
		//check if the memory is enough
		if (fp == NULL) {
			fprintf(stderr, "File couldn't be opened.\n");
			exit(EXIT_FAILURE);
		}
		free (urlArray);
		//print the tree in the file
		showTree(fp, bst);
		//close the file
		fclose (fp);
		//free the tree
		dropTree(bst);
	}
	return EXIT_SUCCESS;
}
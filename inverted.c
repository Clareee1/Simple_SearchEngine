// inverted.c
// Written by Aldhytha Karina Sari (Alina), 21 May 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "BSTree.h"

#define MAX_NUM_OF_URL 100

int main (int argc, char * argv[]) {
	if (argc == 1) {
		int * urlArray = getNameOfUrlFromFile ("collection.txt");
		int numUrl = getNumOfUrlFromFile ("collection.txt");
		int i;
		Tree bst = newTree();
		for (i = 0; i < numUrl; i++) {
			int size = snprintf (NULL, 0, "url%d.txt", urlArray[i]);
			char * tmp = malloc ((size + 1) * sizeof(char));
			if (tmp == NULL) {
				printf("Out of Memory.\n");
				exit (EXIT_FAILURE);
			}
			snprintf(tmp, size + 1, "url%d.txt", urlArray[i]);
//			printf("%s\n", tmp);
			getTxtFromFile (tmp, bst);
		}

		FILE *fp = fopen ("invertedIndex.txt", "w");
		if (fp == NULL) {
			fprintf(stderr, "File couldn't be opened.\n");
			exit(EXIT_FAILURE);
		}
		showTree(fp, bst);
		fclose (fp);
	} else {
		printf("Usage: ./inverted\n");
	}
	return EXIT_SUCCESS;
}
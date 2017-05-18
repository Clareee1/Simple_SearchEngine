//
//  parser.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Create a string array
static char **newStringArray(int size) {
    if (size <= 0) return NULL;

    char **array = malloc(size * sizeof(char*));
    if (array == NULL) exit(1);

    int i;
    for (i = 0; i < size; i++) {
        array[i] = malloc(size * sizeof(char));
        if (array[i] == NULL) exit(1);
    }

    return array;
}
// Get all links from a given webpage
void getUrlTxtFromFile(char *name) {
    if (name == NULL) return;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Count the number of # and count the number of letter 'u'
        char c;
        int hash = 0, url = 0, space = 0;
        while ((c = fgetc(fp)) != EOF) {
            if (c == '#') hash++;
            // Counting for url
            if (hash < 2 && c == 'u') url++;
            // Counting for space
            if (hash < 4 && c == ' ') space++;
            // Done
            if (hash == 4) break;
        }
        // reset fp to start
        rewind(fp);

        char **textArray = newStringArray(space);
        int *nameArray = calloc(url, sizeof(int));
        int urlCount = 0;
        if (nameArray == NULL) exit(1);
        if (textArray != NULL) {
            // Scan all text
            char buffer[64];
            int sectionCount = 0;
            int i;
            for (i = 0; i < space; i++) {
                fscanf(fp, "\n %s ", buffer);
                // TODO Remove comma
                // End of section-1 and the start of section-2
                if (strcmp(buffer, "Section-2") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
                else if (strstr(buffer, "url")) {
                    // YEAH! A url
                    nameArray[urlCount] = getNumFromString(buffer);
                    printf("url%d.txt\n", nameArray[urlCount]);
                    urlCount++;
                } else if (sectionCount == 2) {
                    // This is a keyword
                    strcpy(textArray[i], buffer);
                    printf("%s ", textArray[i]);
                } else if (sectionCount == 3) break; // Done
            }
        }
        printf("\n\n");
    }
}

// Get name of links from collection.txt
int *getNameOfUrlFromFile(char *name, int num) {
    if (name == NULL || num <= 0) return NULL;

    int *nameArray = calloc(num, sizeof(int));
    if (nameArray == NULL) exit(1);

    FILE *fp = fopen(name, "r");
    // Be able to open file
    if (fp != NULL) {
        int i, currNum = 0;
        for (i = 0; i < num; i++) {
            // Read all number into array
            fscanf(fp, "\nurl%d ", &currNum);
            nameArray[i] = currNum;
        }
    }
    fclose(fp);
    return nameArray;
}

// Get number of links from collection.txt
int getNumOfUrlFromFile(char *name) {
    if (name == NULL) return -1;

    int numOfUrl = 0;
    FILE *fp = fopen(name, "r");
    // Be able to open file
    if (fp != NULL) {
        char c;
        // Read until it reaches the end
        while ((c = fgetc(fp)) != EOF) {
            // Count the number of letter "u" from "url"
            if (c == 'u') numOfUrl++;
        }
    }
    fclose(fp);
    return numOfUrl;
}

// Convert url23.txt to 23
int getNumFromString(char *name) {
    if (name == NULL) return -1;

    int num = 0;
    // Assume all string has the format url123.txt / url123
    if (sscanf(name, "url%d.txt", &num)) return num;
    else if (sscanf(name, "url%d", &num)) return num;
    return -1;
}

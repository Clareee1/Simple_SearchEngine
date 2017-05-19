//
//  parser.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

// Convert a string to lower
void strlower(char* str) {
    if (str == NULL) return;
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++) {
        // Convert to lowercase if it is uppercase
        if (isupper(str[i])) str[i] = tolower(str[i]);
    }
}

// Get all links from a given webpage
int getUrlTxtFromFile(char *name, char *nameArray, int *urlArray) {
    if (name == NULL || nameArray == NULL || urlArray == NULL) return -1;

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

        // Scan all text
        char buffer[64];
        int sectionCount = 0;
        int i;
        for (i = 0; i < space; i++) {
            fscanf(fp, "\n %s ", buffer);
            // End of section-1 and the start of section-2
            if (strcmp(buffer, "Section-2") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
            else if (strstr(buffer, "url")) {
                // YEAH! A url
                urlArray[urlCount] = getNumFromString(buffer);
                // printf("url%d.txt\n", urlArray[urlCount]);
                urlCount++;
            } else if (sectionCount == 2) {
                // If it has a full stop at the end, remove it
                if (buffer[strlen(buffer) - 1] == '.') buffer[strlen(buffer) - 1] = '\0';
                // Convert it to lower cased
                strlower(buffer);
                // This is a keyword
                strcpy(nameArray[i], buffer);
                // printf("%s ", nameArray[i]);
            } else if (sectionCount == 3) break; // Done
        }
        printf("\n\n");
        return url;
    }
    return -1;
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

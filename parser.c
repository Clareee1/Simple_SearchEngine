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
    if (array == NULL) return NULL;

    int i;
    for (i = 0; i < size; i++) {
        array[i] = malloc(size * sizeof(char));
        if (array[i] == NULL) return NULL;
    }

    return array;
}

// Convert a string to lower (Henry)
void strlower(char* str) {
    if (str == NULL) return;
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++) {
        // Convert to lowercase if it is uppercase
        if (isupper(str[i])) str[i] = tolower(str[i]);
    }
}

// Get all links from a given webpage (Henry)
int getUrlFromFile(char *name, int *urlArray) {
    if (name == NULL || urlArray == NULL) return -1;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Count the number of # and count the number of letter 'u'
        char c;
        int hash = 0, url = 0;
        while ((c = fgetc(fp)) != EOF) {
            if (c == '#') hash++;
            // Count for url
            if (hash > 2 && c == 'u') url++;
            // Done
            if (hash == 4) break;
        }
        // reset fp to start
        rewind(fp);

        // Scan all text
        char buffer[64];
        int sectionCount = 0;
        int i, urlCount = 0;
        for (i = 0; i < url; i++) {
            fscanf(fp, "\n %s ", buffer);
            // End of section-1 and the start of section-2
            if (strcmp(buffer, "Section-2") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
            else if (strstr(buffer, "url")) {
                // YEAH! A url
                urlArray[urlCount] = getNumFromString(buffer);
                // printf("url%d.txt\n", urlArray[urlCount]);
                urlCount++;
            } else if (sectionCount == 2) {
                // End of urls
                break;
            }
        }
        // printf("\n");
        return urlCount;
    }
    return -1;
}

// Get all links from a given webpage (Henry)
void getTxtFromFile(char *name) {
    // TODO DONT FORGET THE TREE!!!!
    if (name == NULL) return;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Count the number of # and count for space
        char c;
        int hash = 0, space = 0;
        while ((c = fgetc(fp)) != EOF) {
            if (c == '#') hash++;
            // Counting for space
            if (hash >= 2 && hash < 4 && c == ' ') space++;
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
            else if (sectionCount == 2) {
                // If it has a full stop at the end, remove it
                if (buffer[strlen(buffer) - 1] == '.') buffer[strlen(buffer) - 1] = '\0';
                // Convert it to lower cased
                strlower(buffer);
                // This is a keyword
                printf("%s ", buffer);
            } else if (sectionCount == 3) break; // Done
        }
        printf("\n");
    }
}

// Get name of links from collection.txt (Henry)
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

// Get number of links from collection.txt (Henry)
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

// Get the number of keywords from invertedIndex.txt (Part 2) (Henry)
int getNumOfKeywordFromFile(char *name) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    printf("%p\n", fp);
    if (fp != NULL) {
        char buffer[64];
        int wordCount = 0;

        while (fscanf(fp, "\n%s ", buffer) == 1) {
            // Try to get all keywords, ignore urls
            if (!strstr(buffer, "url")) wordCount++;
        }
        printf("f:%d\n", wordCount);
        return wordCount;
    }
    fclose(fp);
    return -1;
}

// Get an array of keywords from invertedIndex.txt (Part 2) (Henry)
char **getKeywordFromFile(char *name, int size) {
    if (name == NULL || size <= 0) return NULL;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        char buffer[64];
        int wordCount = 0;
        char **keywords = newStringArray(size);
        if (keywords == NULL) exit(1);

        while (fscanf(fp, "\n%s ", buffer) == 1) {
            // Try to get all keywords, ignore urls
            if (!strstr(buffer, "url")) {
                strcpy(keywords[wordCount++], buffer);
            }
        }
        return keywords;
    }
    fclose(fp);
    return NULL;
}

// Convert url23.txt to 23 (Henry)
int getNumFromString(char *name) {
    if (name == NULL) return -1;

    int num = 0;
    // Assume all string has the format url123.txt / url123
    if (sscanf(name, "url%d.txt", &num)) return num;
    else if (sscanf(name, "url%d", &num)) return num;
    return -1;
}

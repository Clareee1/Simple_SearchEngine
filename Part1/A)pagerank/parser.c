//
//  parser.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

// Convert a string to lower (Henry)
static void strlower(char* str) {
    if (str == NULL) return;
    int len = strlen(str);
    int i;
    for (i = 0; i < len; i++) {
        // Convert to lowercase if it is uppercase
        if (isupper(str[i])) str[i] = tolower(str[i]);
    }
}

// Normalise a string, return 0 for bad keyword (ignore it) (Henry)
int normalise(char *keyword) {
    if (keyword == NULL) return 0;
    // Make it lower case
    strlower(keyword);
    return 1;
}

// Get all links from a given webpage (Henry)
int getUrlFromFile(char *name, int *urlArray) {
    if (name == NULL || urlArray == NULL) return -1;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Scan all text
        char buffer[64];
        int sectionCount = 0;
        int urlCount = 0;
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            // End of section-1 and the start of section-2
            if (strcmp(buffer, "Section-1") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
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
void getTxtFromFile(char *name, Tree bst) {
    if (name == NULL) return;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Scan all text
        char buffer[64];
        int sectionCount = 0;
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            // End of section-1 and the start of section-2
            if (strcmp(buffer, "Section-2") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
            else if (sectionCount == 2) { // This is a keyword
                // If it has a full stop at the end, remove it
                if (buffer[strlen(buffer) - 1] == '.') buffer[strlen(buffer) - 1] = '\0';
                // Convert it to lower cased
                strlower(buffer);
                // Add it to Binary Tree (Alina)
                int url = getNumFromString(name);
                TreeFindAndInsert(bst, buffer, url);
            } else if (sectionCount == 3) break; // Done
        }
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

// Check if there is such keywords from invertedIndex.txt (Part 2) (Henry)
int hasKeyword(char *name, char *keyword) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    int hasWord = 0;
    char buffer[64];
    if (fp != NULL) {
        while (fscanf(fp, keyword, buffer) == 1) {
            hasWord = 1;
            break;
        }
    }
    return hasWord;
}

// Get the number of links after a keyword from invertedIndex.txt (Part 2) (Henry)
int getNumOfUrlForKeywordFromFile(char *name, char *keyword) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        char buffer[64];
        while (fscanf(fp, keyword, buffer) == 1) {
            while (fscanf(fp, "url%[^0123456789]", buffer) == 1) {

            }
        }
    }
    return -1;
}

// Get all links after a keyword from invertedIndex.txt (Part 2) (Henry)
int *getUrlOfKeywordFromFile(char *name, char *keyword) {
    if (name == NULL) return NULL;

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {

    }
    return NULL;
}

// Convert url23.txt to 23 (Henry)
int getNumFromString(char *name) {
    if (name == NULL) return -1;

    int num = 0;
    // Get  number from string
    if (sscanf(name, "%*[^0123456789]%d%*[^0123456789]", &num) == 1) {
        return num;
    }
    return -1;
}

//
//  parser.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

#define MAX_BUFFER 64

//HELPER FUNCTION

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

// Normalise the word (remove all that's non-alphanumeric and lowercase everything) (Alina)
void normalise (char * word) {
    //lowercase the word
    strlower (word);
    int length = strlen (word);
    int counter = 0;
    int i;
    for (i = 0; i < length; i++) {
        //keep the alphanumeric characters
        if (isalnum(word[i]) != 0) {
            word[counter] = word[i];
            counter++;
        }
    }
    //to keep the string intact
    word[counter] = '\0';
}

// Get name of links from collection.txt (Henry)
void getUrlFromFile(char *name, int *urlArray) {
    if (name == NULL || urlArray == NULL) exit(0);

    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Scan all text
        char buffer[MAX_BUFFER];
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
    }
    fclose(fp);
}

// Get number of links from collection.txt (Henry)
int getNumUrlFromFile(char *name) {
    FILE *fp = fopen(name, "r");
    if (fp != NULL) {
        // Scan all text
        char buffer[MAX_BUFFER];
        int sectionCount = 0;
        int urlCount = 0;
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            // End of section-1 and the start of section-2
            if (strcmp(buffer, "Section-1") == 0 || strcmp(buffer, "#end") == 0) sectionCount++;
            else if (strstr(buffer, "url")) {
                urlCount++;
            } else if (sectionCount == 2) {
                break;
            }
        }
        // printf("\n");
        fclose(fp);
        return urlCount;
    }
    fclose(fp);
    return -1;
}

//Get all links from a given webpage (Henry)
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
                // normalise it
                normalise(buffer);
                // Add it to Binary Tree (Alina)
                int url = getNumFromString(name);
                TreeFindAndInsert(bst, buffer, url);
            } else if (sectionCount == 3) break; // Done
        }
    }
    fclose(fp);
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
        char buffer[MAX_BUFFER];
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            if (strstr(buffer, "url")) numOfUrl++;
        }
    }
    fclose(fp);
    return numOfUrl;
}

// Get the number of links for a keyword from invertedIndex.txt (Part 1B) (Alina)
// Added for convenience purposes (Alina)
int getNumOfUrlForKeywordFromFile(char *name, char *keyword) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    int count = 0;
    if (fp != NULL) {
        char buffer[512];
        // Read line by line until keyword is reached
        while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
            if (strstr(buffer, keyword)) {
                char *url = strtok(buffer, " ");
                while ((url = strtok(NULL, " "))) {
                    if (strstr(url, "url")) {
                        count++;
                    }
                }
                break;
            }
        }
    }
    fclose(fp);
    return count;
}

// Get the name of links for a keyword from invertedIndex.txt (Part 2) (Henry)
// Changed the return value to none (Alina)
void getNameOfUrlForKeywordFromFile(char *name, char *keyword, int *array) {
    if (name == NULL) return;

    FILE *fp = fopen(name, "r");
    int count = 0;
    if (fp != NULL) {
        char buffer[512];
        // Read line by line until keyword is reached
        while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
            if (strstr(buffer, keyword)) {
                char *url = strtok(buffer, " ");
                while ((url = strtok(NULL, " "))) {
                    if (strstr(url, "url")) {
                        array[count] = getNumFromString(url);
                        count++;
                    }
                }
                break;
            }
        }
    }
    fclose(fp);
}

// Get number of keywords from invertedIndex.txt (Part 2) (Henry)
int getNumOfKeywordFromFile(char *name) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    int count = 0;
    if (fp != NULL) {
        char c;
        // Read how many lines we have
        while ((c = getc(fp)) != EOF) {
            if (c == '\n') count++;
        }
    }
    fclose(fp);
    return count;
}

// Count how many times a keyword appeared in one url (Part 2) (Henry)
int getKeywordCountFromUrl(char *name, char *keyword) {
    if (name == NULL || keyword == NULL) return -1;

    FILE *fp = fopen(name, "r");
    int count = 0;
    if (fp != NULL) {
        char buffer[64];
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            normalise(buffer);
            // We found that word, YEAH!
            if (strcmp(buffer, keyword) == 0) count++;
        }
    }
    fclose(fp);
    return count;
}

// Check if there is such keywords from invertedIndex.txt (Part 2) (Henry)
int hasKeyword(char *name, char *keyword) {
    if (name == NULL) return -1;

    FILE *fp = fopen(name, "r");
    int count = 0;
    if (fp != NULL) {
        char buffer[MAX_BUFFER];
        while (fscanf(fp, "\n %s ", buffer) == 1) {
            normalise(buffer);
            // We found that word, YEAH!
            if (strcmp(buffer, keyword) == 0) {
                count = 1;
                break;
            }
        }
    }
    fclose(fp);
    return count;
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

// Convert 23 to url23 (Alina)
char * getStringFromNum (int num) {
    // get the size of the urlxx
    int size = snprintf (NULL, 0, "url%d", num);
    char * name = malloc ((size + 1) * sizeof(char));
    if (name == NULL) {
        printf("Out of Memory.\n");
        exit (EXIT_FAILURE);
    }
    // converting 23 to url23
    snprintf(name, size + 1, "url%d", num);
    // return to the calling function
    return name;
}

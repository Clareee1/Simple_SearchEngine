//
//  parser.c
//  Created by Henry Quan on 15/05/17.
//

#include <stdio.h>

/*// Get all links from a given webpage
void getUrlFromFile(char *, Graph url) {

}

// Get all texts from a given webpage
void getTxtFromFile(char *, BST keyword) {

}*/

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
    // Assume all string has the format url123.txt
    if (sscanf(name, "url%d.txt", &num)) {
        return num;
    } return -1;
}

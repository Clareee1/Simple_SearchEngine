//
//  parser.h
//  Created by Henry Quan on 15/05/17.
//

#ifndef PARSER_H
#define PARSER_H
// #include "BSTree.h"

// Get all links from a given webpage (Part 1 A) (Henry)
int getUrlFromFile(char *, int *);
// Get all texts from a given webpage (Part 1 B, 1 C) (Henry)
// void getTxtFromFile(char *, Tree);
// Get name of links from collection.txt (Henry)
int *getNameOfUrlFromFile(char *, int);
// Get number of links from collection.txt (Henry)
int getNumOfUrlFromFile(char *);
// Convert url23.txt to 23 (Henry)
int getNumFromString(char *);

// Check if there is such keywords from invertedIndex.txt (Part 2) (Henry)
int hasKeyword(char *, char *);
// Get the name of links for a keyword from invertedIndex.txt (Part 2) (Henry)
int getNameOfUrlForKeywordFromFile(char *, char *, int *);
// Get number of keywords from invertedIndex.txt (Part 2) (Henry)
int getNumOfKeywordFromFile(char *);
// Count how many times a keyword appeared in one url (Part 2) (Henry)
int getKeywordCountFromUrl(char *, char *);

// Convert a string to lower (Henry)
void strlower(char* str);

#endif

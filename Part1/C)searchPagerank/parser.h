//
//  parser.h
//  Created by Henry Quan on 15/05/17.
//

#ifndef PARSER_H
#define PARSER_H

#include "BSTree.h"

// Convert a string to lower (Henry)
void strlower(char* str);
// Normalise the word (remove all that's non-alphanumeric and lowercase everything)
void normalise (char * word);
// Get all links from a given webpage (Part 1 A) (Henry)
int getNumUrlFromFile(char *);
// Get all texts from a given webpage (Part 1 B, 1 C) (Henry)
void getTxtFromFile(char *, Tree);
// Get name of links from collection.txt (Henry)
void getUrlFromFile(char* ,int*);
//Get all texts from a given webpage (Part 1 B, 1 C) (Henry)
void getTxtFromFile(char *, Tree);
// Get name of links from collection.txt (Henry)
int *getNameOfUrlFromFile(char *, int);
// Get number of links from collection.txt (Henry)
int getNumOfUrlFromFile(char *);
// Convert url23.txt to 23 (Henry)
int getNumFromString(char *);
// Convert 23 to url23.txt (Alina)
char * getStringFromNum (int num);

// Check if there is such keywords from invertedIndex.txt (Part 2) (Henry)
int hasKeyword(char *, char *);
// Get the number of links for a keyword from invertedIndex.txt (Part 2) (Henry)
int getNumOfUrlForKeywordFromFile(char *, char *);
// Get the name of links for a keyword from invertedIndex.txt (Part 2) (Henry)
void getNameOfUrlForKeywordFromFile(char *, char *, int *);
// Get number of keywords from invertedIndex.txt (Part 2) (Henry)
int getNumOfKeywordFromFile(char *);
// Count how many times a keyword appeared in one url (Part 2) (Henry)
int getKeywordCountFromUrl(char *, char *);

#endif

//
//  parser.h
//  Created by Henry Quan on 15/05/17.
//

#ifndef PARSER_H
#define PARSER_H

// Get all links from a given webpage (Part 1 A) (Henry)
int getUrlFromFile(char *, int *);
// Get all texts from a given webpage (Part 1 B, 1 C) (Henry)
// TODO getTxtFromFile(char *, Tree) -> Add binary tree
void getTxtFromFile(char *);
// Get name of links from collection.txt (Henry)
int *getNameOfUrlFromFile(char *, int);
// Get number of links from collection.txt (Henry)
int getNumOfUrlFromFile(char *);
// Convert url23.txt to 23 (Henry)
int getNumFromString(char *);

// Get the number of keywords from invertedIndex.txt (Part 2) (Henry)
int getNumOfKeywordFromFile(char *);
// Get an array of keywords from invertedIndex.txt (Part 2) (Henry)
char **getKeywordFromFile(char *, int);

#endif

//
//  parser.h
//  Created by Henry Quan on 15/05/17.
//

#ifndef PARSER_H
#define PARSER_H

// Get all links from a given webpage (Part A)
int getUrlFromFile(char *, int *);
// Get all texts from a given webpage (Part B, C)
// TODO getTxtFromFile(char *, Tree) -> Add binary tree
void getTxtFromFile(char *);
// Get name of links from collection.txt
int *getNameOfUrlFromFile(char *, int);
// Get number of links from collection.txt
int getNumOfUrlFromFile(char *);
// Convert url23.txt to 23
int getNumFromString(char *);

#endif

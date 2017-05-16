//
//  parser.h
//  Created by Henry Quan on 15/05/17.
//

#ifndef PARSER_H
#define PARSER_H

// Get all linksn and texts from a given webpage
void getUrlTxtFromFile(char *);
// Get name of links from collection.txt
int *getNameOfUrlFromFile(char *, int);
// Get number of links from collection.txt
int getNumOfUrlFromFile(char *);
// Convert url23.txt to 23
int getNumFromString(char *);

#endif

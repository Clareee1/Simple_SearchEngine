# Calculate PageRanks
You need to write a program in the file pagerank.c that reads data from a given collection of pages in the file collection.txt and builds a graph structure using Adjacency Matrix or List Representation. Using the algorithm described below, calculate PageRank for every url in the file collection.txt. In this file, urls are separated by one or more spaces or/and new line character. Add suffix .txt to a url to obtain file name of the corresponding "web page". For example, file url24.txt contains the required information for url24.

## Example file collection.txt
url25   url31 url2
url102   url78
url32  url98 url33

Your program in pagerank.c will take three arguments (d - damping factor, diffPR - difference in PageRank sum, maxIterations - maximum iterations) and using the algorithm described in this section, calculate PageRank for every url.

## For example
% pagerank 0.85  0.00001  1000

Your program should output a list of urls in descending order of PageRank values (to 8 significant digits) to a file named pagerankList.txt. The list should also include out degrees (number of out going links) for each url, along with its PageRank value. The values in the list should be comma separated. For example, pagerankList.txt may contain the following:

Example file pagerankList.txt

    url31, 3, 0.2623546
    url21, 1, 0.1843112
    url34, 6, 0.1576851
    url22, 4, 0.1520093
    url32, 6, 0.0925755
    url23, 4, 0.0776758
    url11, 3, 0.0733884

[More Information](https://www.cse.unsw.edu.au/~cs1927/17s1/ass/ass02/Ass2.html)

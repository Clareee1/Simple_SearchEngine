# Part 2: Content-based Search Engine
In this part, you need to implement a content-based search engine that uses tf-idf values of all query terms for ranking. You need to calculate tf-idf values for each query term in a page, and rank pages based on the summation of tf-idf values for all query terms. Use "inverted index" you created in Part-1 to locate matching pages for query terms.

## Goal
calculate term frequency tf(t,d) using the raw frequency of a term in a document, i.e. the number of times that term t occurs in document d. See the example below.
calculate inverse document frequency idf(t, D) by dividing the total number of documents by the number of documents containing the term

Write a content-based search engine in file searchTfIdf.c that given search terms (words) as commandline arguments, outputs (to stdout) top ten pages in descending order of summation of tf-idf values of all search terms (as described above). Your program must also output the corresponding summation of tf-idf along with each page, separated by a space and using format "%.6f", see example below.

If number of matches are less than 10, output all of them. Your program must use data available in two files invertedIndex.txt and collection.txt, and must derive result from them. We will test this program independently to your solutions for Part-1.

### Example
./searchTfIdf  mars  design
url25  1.902350
url31  0.434000

[More Information](https://www.cse.unsw.edu.au/~cs1927/17s1/ass/ass02/Ass2.html)

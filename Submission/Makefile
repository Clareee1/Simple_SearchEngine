CC=gcc
CFLAGS=-g -Werror -Wall

all: pagerank inverted	search	tdidf part3
pagerank:
	$(CC) $(CFLAGS) pagerank.c graph.c BSTree.c IntList.c parser.c -o pagerank
	valgrind ./pagerank 0.85  0.00001  1000
inverted:
	$(CC) $(CFLAGS) inverted.c graph.c BSTree.c IntList.c parser.c -o inverted
	valgrind ./inverted
search:
	$(CC) $(CFLAGS) searchPagerank.c graph.c BSTree.c IntList.c parser.c -o search
	valgrind ./search mars  design
tdidf:
	$(CC) $(CFLAGS) searchTfIdf.c graph.c BSTree.c IntList.c parser.c -lm -o tdidf
	valgrind ./tdidf  mars  design
part3:
	$(CC) $(CFLAGS) scaledFootrule.c ArrayList.c graph.c BSTree.c IntList.c parser.c -o part3
	valgrind ./part3 rankA.txt rankD.txt
clean:
	rm -f *.exe
	rm -f pagerank inverted search tdidf part3 invertedIndex.txt pagerankList.txt

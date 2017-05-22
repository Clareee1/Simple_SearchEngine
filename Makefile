CC=gcc
FLAGS=-Wall -Werror -g

all:
	$(CC) $(FLAGS) *.c -o test
pagerank:
	$(CC) $(FLAGS) parser.c graph.c pagerank.c -o pagerank
inverted:
	$(CC) $(FLAGS) parser.c BSTree.c IntList.c inverted.c -o inverted
parser:
	$(CC) $(FLAGS) parser.c BSTree.c IntList.c testUnit.c -o parser
pagerank:
	$(CC) $(FLAGS) parser.c graph.c pagerank.c BSTree.c IntList.c -o pagerank
tdidf:
	$(CC) $(FLAGS) parser.c Part2/searchTfIdf.c -o searchTfIdf
	rm Part2/searchTfIdf.exe
	mv searchTfIdf.exe Part2/searchTfIdf.exe
	cd Part2
clean:
	rm -f *.exe Part2/*.exe
	rm -f test pagerank inverted Part2/searchTfIdf

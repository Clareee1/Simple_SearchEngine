CC=gcc
FLAGS=-Wall -Werror -g

all:
	$(CC) $(FLAGS) *.c -o test
pagerank:
	$(CC) $(FLAGS) parser.c graph.c pagerank.c -o pagerank
parser:
	$(CC) $(FLAGS) parser.c testUnit.c -o parser
tdidf:
	$(CC) $(FLAGS) parser.c Part2/searchTfIdf.c -o searchTfIdf
	rm Part2/searchTfIdf.exe
	mv searchTfIdf.exe Part2/searchTfIdf.exe
	cd Part2
clean:
	rm -f *.exe

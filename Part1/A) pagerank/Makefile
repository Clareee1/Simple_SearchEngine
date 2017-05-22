CC=gcc
FLAGS=-Wall -Werror -g

pagerank:
	$(CC) $(FLAGS) parser.c graph.c pagerank.c BSTree.c IntList.c -o pagerank
test:
	$(CC) $(FLAGS) parser.c graph.c pagerank.c BSTree.c IntList.c -o pagerank
	cp pagerank.exe Examples/1aEx1
	cp pagerank.exe Examples/1aEx2
	cp pagerank.exe Examples/1aEx3
clean:
	rm -f *.exe
	rm -f pagerank pagerankList.txt

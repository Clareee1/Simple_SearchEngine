CC=gcc
CFLAGS=-Wall -Werror -g

bruteforce:
	$(CC) $(CFLAGS) ArrayList.c BruteForce.c -o bruteforce
	./bruteforce rankA.txt rankD.txt
	./bruteforce rankB.txt rankC.txt
test:
	$(CC) $(CFLAGS) ArrayList.c testArrayList.c -o test
permutation:
	$(CC) $(CFLAGS) permutation.c -o permutation
permutationR:
	$(CC) $(CFLAGS) permutationR.c -o permutationR
clean:
	rm -f *.exe test permutation

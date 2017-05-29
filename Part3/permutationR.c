//
//  permutationR.c
//  Created by Henry Quan on 29/05/17.
//

#include <stdio.h>
#include <stdlib.h>

// Permutation
void permute(int *numbers, int start, int length);
// Swap index
void swap(int *numbers, int i, int j);
// Print out array
void printArray(int *number, int length);

int main(int argc, char *argv[]) {
    if (argc > 1 && argc < 3) {
        int size = atoi(argv[1]);
        int *array = calloc(size, sizeof(int));
        int i;
        for (i = 1; i <= size; i++) {
            array[i - 1] += i;
        }
        permute(array, 0, size);
    }
    return 0;
}

void printArray(int *number, int length) {
    int i;
    for (i = 0; i < length; i++) printf("%d ", number[i]);
    printf("\n");
}

void swap(int *numbers, int i, int j)
{
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
}

void permute(int *numbers, int start, int length)
{
    if(start == length)
    {
        printArray(numbers, length);
        return;
    }

    permute(numbers, start + 1, length);
    int i;
    for(i = start + 1; i < length; i++)
    {
        if(numbers[start] == numbers[i])
            continue;
        swap(numbers, start, i);
        permute(numbers, start + 1, length);
        swap(numbers, start, i);
    }
}

//
//  permutation.c
//  Created by Henry Quan on 29/05/17.
//

#include <stdio.h>
#include <stdlib.h>

// Permutation
void permute(int *numbers, int length);
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
        permute(array, size);
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

int *intdup(int *numbers, int length) {
    if (numbers == NULL) return NULL;
    int *cpy = malloc(length * sizeof(int));
    if (cpy == NULL) return NULL;

    int i;
    for (i = 0; i < length; i++) {
        cpy[i] = numbers[i];
    }
    return cpy;
}

static int f(int number) {
    if (number == 0) return 1;
    if (number == 1) return 1;
    return number * f(number - 1);
}

void permute(int *numbers, int length)
{
    if (length == 1) {
        printArray(numbers, length);
    } else if (length == 2) {
        printArray(numbers, length);
        swap(numbers, 0, 1);
        printArray(numbers, length);
    } else if (length > 2) {
        int i, j, k = 1;
        int number = 0;
        int *temp = intdup(numbers, length);
        for (i = 0; i < length; i++) {
            // Swap (1, 2), (3, 4)...
            // Then swap(3, 4), (5, 6)...
            int array[4] = {1, 2, length - 2, 2};
            int count = 0;
            int factorial = f(length - 1);
            for (j = 0; j <= factorial; j++) {
                int index = j % 3;
                k = array[index];
                if (index < 3) {
                    while (k + 1 < length && count < factorial) {
                        swap(numbers, k, k + 1);
                        printArray(numbers, length);
                        k += 2;
                        count++;
                        number++;
                    }
                } else {
                    while (k > 0 && count < factorial) {
                        swap(numbers, k, k + 1);
                        printArray(numbers, length);
                        k -= 2;
                        count++;
                        number++;
                    }
                }
                if (count == factorial) break;
            }
            numbers = intdup(temp, length);
            swap(numbers, 0, i + 1);
        }
        printf("%d\n", number);
    } else {
        return;
    }
}

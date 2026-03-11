#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE (512 * 1024 * 1024 / sizeof(int))

int main() {
    int *arr = malloc(SIZE * sizeof(int));
    if (!arr) return 1;

    // initialize
    for (size_t i = 0; i < SIZE; i++)
        arr[i] = i;

    long long sum = 0;

    clock_t start = clock();

    // SEQUENTIAL ACCESS
    for (size_t i = 0; i < SIZE; i++)
        sum += arr[i];

    // RANDOM ACCESS
    for (size_t i = 0; i < SIZE; i++) {
        size_t idx = rand() % SIZE;
        sum += arr[idx];
    }
    clock_t end = clock();

    printf("Sum: %lld\n", sum);
    printf("Time: %f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    free(arr);
    return 0;
}
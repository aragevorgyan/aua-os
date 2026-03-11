// memory_bound.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

int main() {
    int *arr = malloc(N * sizeof(int));

    for (long i = 0; i < N; i++)
        arr[i] = i;

    volatile long sum = 0;

    for (long i = 0; i < N; i++)
        sum += arr[rand() % N];   // random access (cache miss heavy)

    printf("Sum: %ld\n", sum);
    free(arr);
    return 0;
}
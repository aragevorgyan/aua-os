#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    const int N = 100000000;
    int *arr = malloc(N * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Fill array with some values
    for (int i = 0; i < N; i++) {
        arr[i] = i % 1000;
    }

    // Put a known large value somewhere
    arr[543210] = 999999;

    int max = arr[0];

    double start = omp_get_wtime();

    for (int i = 1; i < N; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    double end = omp_get_wtime();

    printf("Maximum = %d\n", max);
    printf("Time = %f seconds\n", end - start);

    free(arr);
    return 0;
}

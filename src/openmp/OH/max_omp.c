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

    int global_max = arr[0];

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(4) shared(arr, global_max)
    {
        int local_max = arr[0];   // private for each thread

        #pragma omp for
        for (int i = 0; i < N; i++) {
            if (arr[i] > local_max) {
                local_max = arr[i];
            }
        }

        // Only when a thread finished its own part,
        // it updates the global maximum
        #pragma omp critical
        {
            if (local_max > global_max) {
                global_max = local_max;
            }
        }
    }

    double end = omp_get_wtime();

    printf("Maximum = %d\n", global_max);
    printf("Time = %f seconds\n", end - start);

    free(arr);
    return 0;
}

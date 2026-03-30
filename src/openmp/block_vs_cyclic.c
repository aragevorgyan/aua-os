#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200000000  // Large enough to see cache effects
#define REPEAT 3     // Run multiple times for stability

int main() {
    int *arr = (int *)malloc(sizeof(int) * N);
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Threads: %d\n\n", omp_get_max_threads());

    for (int r = 0; r < REPEAT; r++) {

        // STATIC (block)
        double start = omp_get_wtime();

        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; i++) {
            arr[i] = i;
        }

        double t_static = omp_get_wtime() - start;

        // CYCLIC (static,1)
        start = omp_get_wtime();

        #pragma omp parallel for schedule(static, 1)
        for (int i = 0; i < N; i++) {
            arr[i] = i;
        }

        double t_cyclic = omp_get_wtime() - start;

        printf("Run %d:\n", r + 1);
        printf("  static      : %f sec\n", t_static);
        printf("  static,1    : %f sec\n", t_cyclic);
        printf("\n");
    }

    free(arr);
    return 0;
}
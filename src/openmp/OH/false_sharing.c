#include <stdio.h>
#include <omp.h>

#define N 8

int main() {
    int arr[N] = {0};

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (long j = 0; j < 100000000; j++) {
            arr[i]++;
        }
    }

    double end = omp_get_wtime();

    printf("Time: %f\n", end - start);
    return 0;
}

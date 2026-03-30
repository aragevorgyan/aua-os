#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000
#define MAX_THREADS 8
#define CACHE_LINE 64

// Each element occupies its own cache line
typedef struct {
    long long value;
    char padding[CACHE_LINE - sizeof(long long)];
} padded_sum_t;

int main() {
    int *arr = malloc(N * sizeof(int));
    padded_sum_t sub_sums[MAX_THREADS];

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    // Initialize partial sums
    for (int i = 0; i < MAX_THREADS; i++) {
        sub_sums[i].value = 0;
    }

    int num_threads = 0;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(8)
    {
        int tid = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        #pragma omp single
        num_threads = total_threads;

        int chunk = N / total_threads;
        int start = tid * chunk;
        int end = (tid == total_threads - 1) ? N : start + chunk;

        // IMPORTANT: use local accumulator (register)
        long long local_sum = 0;

        for (int i = start; i < end; i++) {
            local_sum += arr[i];
        }

        // Single write per thread → no contention
        sub_sums[tid].value = local_sum;
    }

    end_time = omp_get_wtime();

    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        total_sum += sub_sums[i].value;
    }

    printf("Total Sum = %lld\n", total_sum);
    printf("Parallel Execution Time: %f seconds\n", end_time - start_time);

    free(arr);
    return 0;
}
#include <stdio.h>
#include <omp.h>

#define N 1000000  // Increase array size for better time measurement
#define MAX_THREADS 8  // Adjust based on CPU

int main() {
    int arr[N];
    long long sub_sums[MAX_THREADS] = {0};  // Array for partial sums

    // Initialize array with values 1, 2, 3, ..., N
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    int num_threads = 0;
    double start_time, end_time;  // Variables for timing

    // Start measuring time
    start_time = omp_get_wtime();

    // Compute sum using OpenMP parallelization
    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        num_threads = total_threads;  // Capture total threads dynamically

        int chunk_size = N / total_threads;  // Base chunk size per thread
        int start = thread_id * chunk_size;  // Start index for this thread
        int end = (thread_id == total_threads - 1) ? N : start + chunk_size;  // Last thread takes remaining elements

        // Each thread computes its partial sum
        for (int i = start; i < end; i++) {
            sub_sums[thread_id] += arr[i];
        }
    }

    // Stop measuring time
    end_time = omp_get_wtime();

    // Compute final sum by adding all partial sums
    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        total_sum += sub_sums[i];
    }

    // Print the results
    printf("Total Sum = %lld\n", total_sum);
    printf("Parallel Execution Time: %f seconds\n", end_time - start_time);

    return 0;
}

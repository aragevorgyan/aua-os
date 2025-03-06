#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int arr[N], sum = 0;

    // Initialize array
    for (int i = 0; i < N; i++)
        arr[i] = i + 1;  // Fill with numbers 1 to N

    #pragma omp parallel
    {
        int local_sum = 0;
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Each thread gets a contiguous chunk
        int chunk_size = N / num_threads;
        int start = id * chunk_size;
        int end = (id == num_threads - 1) ? N : start + chunk_size;  // Last thread handles remainder

        for (int i = start; i < end; i++)
            local_sum += arr[i];

        // Critical section to safely update the global sum
        #pragma omp critical
        sum += local_sum;

        // Ensure all threads finish before printing
        #pragma omp barrier  

        // Ensure only one thread prints the final sum
        #pragma omp single
        printf("Final sum is: %d\n", sum);
    }

    return 0;
}

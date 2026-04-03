#include <stdio.h>
#include <omp.h>

// try changing the number of threads using region export OMP_NUM_THREADS=16

int main() {
    int max_threads = omp_get_max_threads();

    printf("Max available threads: %d\n", max_threads);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int total = omp_get_num_threads();

        #pragma omp critical
        {
            printf("Hello from thread %d out of %d\n", tid, total);
        }
    }

    return 0;
}
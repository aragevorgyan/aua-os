#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;

    // Ask the user for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Parallel region where each thread will print its ID
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        printf("world(%d)\n", ID);
    }

    return 0;
}

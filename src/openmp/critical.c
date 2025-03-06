#include <stdio.h>
#include <omp.h>

int main() {
    int count = 0;  // Shared variable

    #pragma omp parallel num_threads(4)
    {
        // Start of critical section
        #pragma omp critical
        {
            // Only one thread can enter here at a time
            count++;
            printf("Thread %d: count = %d\n", omp_get_thread_num(), count);
        }
        // End of critical section
    }

    printf("Final count = %d\n", count);
    return 0;
}
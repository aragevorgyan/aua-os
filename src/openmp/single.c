#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 0;

    #pragma omp parallel
    {
        // Only one thread executes this block
        #pragma omp single
        {
            shared_var = 100;  // Initialization done by one thread
            printf("Thread %d initialized shared_var to %d\n", omp_get_thread_num(), shared_var);
        }

        // All threads continue from here
        printf("Thread %d reads shared_var = %d\n", omp_get_thread_num(), shared_var);
    }

    return 0;
}

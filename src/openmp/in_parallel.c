#include <stdio.h>
#include <omp.h>

int main() {
    // Outside parallel region
    printf("Outside parallel: %d\n", omp_in_parallel());

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        printf("Thread %d -> inside parallel: %d\n",
               tid, omp_in_parallel());
    }

    return 0;
}
#include <stdio.h>
#include <unistd.h>   // sleep
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();

        // Phase 1: each thread works for different time
        printf("Thread %d: starting phase 1\n", tid);
        sleep(tid + 1);   // different workload per thread
        printf("Thread %d: finished phase 1\n", tid);

        // Synchronization point
        #pragma omp barrier

        // Phase 2: must start together
        printf("Thread %d: starting phase 2\n", tid);
    }

    return 0;
}
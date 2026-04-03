#include <stdio.h>
#include <unistd.h>
#include <omp.h>

// export OMP_WAIT_POLICY=ACTIVE
// export OMP_WAIT_POLICY=PASSIVE

int main() {
    #pragma omp parallel num_threads(8)
    {
        int tid = omp_get_thread_num();

        if (tid == 0) {
            // Simulate long work
            sleep(5);
        }

        // All threads wait here
        #pragma omp barrier

        printf("Thread %d passed barrier\n", tid);
    }

    return 0;
}
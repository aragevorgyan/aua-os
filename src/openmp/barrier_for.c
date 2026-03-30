#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < 4; i++) {
            sleep(1);
            printf("Thread %d finished i=%d\n", tid, i);
        }

        printf("Thread %d passed loop\n", tid);
    }
}
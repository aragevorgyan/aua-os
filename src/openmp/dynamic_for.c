#include <stdio.h>
#include <unistd.h>   // for sleep()
#include <omp.h>

#define N 16

int main() {

    //#pragma omp parallel for schedule(static, 1)
    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < N; i++) {

        // Simulate uneven workload
        if (i % 3 == 0)
            sleep(5);   // heavy work
        else
            usleep(100000); // light work

        printf("Thread %d handled i=%d\n",
               omp_get_thread_num(), i);
    }

    return 0;
}
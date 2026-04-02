#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < 4; i++) {
            sleep(1);
            printf("Loop done by %d\n", omp_get_thread_num());
        }

        printf("After loop: %d\n", omp_get_thread_num());
    }
}

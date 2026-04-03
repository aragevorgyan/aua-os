#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int last_val = -1;

    #pragma omp parallel for //lastprivate(last_val)
    for (i = 0; i < 16; i++) {
        last_val = i;
        printf("Thread %d processes i=%d\n",
               omp_get_thread_num(), i);
    }

    printf("After loop, last_val = %d\n", last_val);

    return 0;
}
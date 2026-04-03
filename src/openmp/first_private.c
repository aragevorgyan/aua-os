#include <stdio.h>
#include <omp.h>

int main() {
    int x = 100;

    printf("Before parallel region, x = %d\n", x);

    #pragma omp parallel firstprivate(x)
    {
        printf("Thread %d: initial x = %d\n",
               omp_get_thread_num(), x);

        x = omp_get_thread_num();
        printf("Thread %d: updated x = %d\n",
               omp_get_thread_num(), x);
    }

    printf("After parallel region, x = %d\n", x);

    return 0;
}
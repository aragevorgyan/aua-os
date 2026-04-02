#include <stdio.h>
#include <omp.h>
int main()
{
#pragma omp parallel
{
    if (omp_get_thread_num() == 0) {
        printf("Manual master\n");
    }

    #pragma omp master
    printf("Master directive\n");

    #pragma omp single
    printf("Single directive\n");
}

    return 0;
}

#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum = sum + i;
    }

    printf("sum = %d\n", sum);
    return 0;
}


/*
int sum = 0;

#pragma omp parallel
{
    int sum_private = 0;

    #pragma omp for
    for (int i = 0; i < N; i++) {
        sum_private += i;
    }

    #pragma omp critical
    {
        sum += sum_private;
    }
}
*/
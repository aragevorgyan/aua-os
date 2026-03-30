#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int sum = 0;

    // Loop-carried dependency on 'sum'
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical
        sum = sum + i;
    }

    printf("sum = %d\n", sum);
    return 0;
}
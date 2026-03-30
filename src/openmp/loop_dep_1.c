#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int A[N];

    A[0] = 1;

    #pragma omp parallel for
    for (int i = 1; i < N; i++) {
        A[i] = A[i - 1] + 1;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }

    return 0;
}
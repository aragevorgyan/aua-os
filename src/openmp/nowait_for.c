#include <stdio.h>
#include <omp.h>

#define N 8

int main() {
    int A[N], B[N];

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        // First loop
        #pragma omp for //nowait
        for (int i = 0; i < N; i++) {
            A[i] = i * 2;
            printf("Thread %d finished A[%d]\n", id, i);
        }

        // No barrier here, threads continue immediately

        // Second loop
        #pragma omp for
        for (int i = 0; i < N; i++) {
            B[i] = A[i] + 1;
            printf("Thread %d finished B[%d]\n", id, i);
        }
    }

    return 0;
}
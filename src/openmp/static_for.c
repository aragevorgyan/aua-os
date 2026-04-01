#include <stdio.h>
#include <omp.h>

#define N 32

int main() {
    int arr[N];

    // Parallel for loop
    #pragma omp parallel num_threads(8)
    #pragma omp for schedule(static, 8)
    for (int i = 0; i < N; i++) {
        arr[i] = i * i;

        printf("Thread %d handles i=%d\n",
               omp_get_thread_num(), i);
    }

    // Print results (sequential)
    printf("\nResults:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;

    double start = omp_get_wtime();
    
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 1000000; i++) {
	#pragma omp critical
        counter++;  // race condition
    }

    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);

    printf("Counter = %d\n", counter);
    return 0;
}

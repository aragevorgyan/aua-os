#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000
#define MAX_CODE 1000

int main() {
    int *log = malloc(N * sizeof(int));

    // Generate fake log data
    for (int i = 0; i < N; i++) {
        log[i] = rand() % MAX_CODE;
    }

    int global_freq[MAX_CODE] = {0};

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {
        int local_freq[MAX_CODE] = {0};  // private per thread

        #pragma omp for
        for (int i = 0; i < N; i++) {
	    #pragma omp critical
	    global_freq[log[i]]++;
            //local_freq[log[i]]++;
        }

	/*
        // merge results
        #pragma omp critical
        {
            for (int i = 0; i < MAX_CODE; i++) {
                global_freq[i] += local_freq[i];
            }
        }
	*/
    }

    double end = omp_get_wtime();

    printf("Frequency of code 404 = %d\n", global_freq[404]);
    printf("Time = %f\n", end - start);

    free(log);
    return 0;
}

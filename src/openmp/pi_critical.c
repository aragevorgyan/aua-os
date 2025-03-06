#include <omp.h>
#include <stdio.h>

static long num_steps = 100000000;
#define NUM_THREADS 2

int main() {
    double pi = 0.0, step;
    double start_time, run_time;
    step = 1.0 / (double) num_steps;
    
    omp_set_num_threads(NUM_THREADS);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthreads;
        double x, sum;
        
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        
        if (id == 0)
            nthreads = omp_get_num_threads();

        for (i = id, sum = 0.0; i < num_steps; i += nthreads) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        
        sum = sum * step;

        #pragma omp critical
        pi += sum;
    }
    run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
    return 0;
}

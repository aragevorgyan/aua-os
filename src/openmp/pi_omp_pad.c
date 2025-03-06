#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 32
#define PAD 8

static long num_steps = 1000000000;
double step;
double start_time, run_time;

int main() {
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    step = 1.0 / (double)num_steps;
    
    omp_set_num_threads(NUM_THREADS);

	start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        
        if (id == 0)
            nthreads = nthrds;
        
        for (i = id, sum[id][0] = 0.0; i < num_steps; i += nthrds) {
            x = (i + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }
    
    for (i = 0, pi = 0.0; i < nthreads; i++)
        pi += sum[i][0] * step;
    
	run_time = omp_get_wtime() - start_time;
    printf("Calculated PI: %lf\n", pi);
	printf("OMP\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
    
    return 0;
}


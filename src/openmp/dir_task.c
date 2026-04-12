#include <stdio.h>
#include <unistd.h>
#include <omp.h>

void process_dir(int depth) {
    if (depth == 0) return;

    printf("Dir depth %d by thread %d\n",
           depth, omp_get_thread_num());

    sleep(1);

    #pragma omp task
    process_dir(depth - 1);

    #pragma omp task
    process_dir(depth - 1);

    #pragma omp taskwait
}

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        process_dir(3);
    }
}
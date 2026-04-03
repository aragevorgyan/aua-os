#include <stdio.h>
#include <omp.h>

int main() {
    int procs = omp_get_num_procs();

    printf("Number of processors available: %d\n", procs);

    return 0;
}
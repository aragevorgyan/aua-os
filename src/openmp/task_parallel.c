#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        for (int i = 1; i <= 4; i++) {
            int val = i;

            #pragma omp task
            {
                #pragma omp atomic
                sum += val;
                printf("Adding %d by thread %d\n",
                       val, omp_get_thread_num());
            }
        }
    }

    printf("Final sum = %d\n", sum);
    return 0;
}
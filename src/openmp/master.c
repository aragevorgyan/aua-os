#include <stdio.h>
#include <omp.h>

int main() {

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        printf("Thread %d is working\n", id);

        #pragma omp master
        {
            printf("Master thread (id = %d) is doing special work\n", id);
        }

        printf("Thread %d continues\n", id);
    }

    return 0;
}
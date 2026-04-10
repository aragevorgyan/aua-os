#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            printf("Creating tasks...\n");

            for (int i = 0; i < 4; i++) {
                int id = i;

                #pragma omp task firstprivate(id)
                {
                    printf("Task %d started on thread %d\n",
                           id, omp_get_thread_num());

                    sleep(2);  // simulate work

                    printf("Task %d finished on thread %d\n",
                           id, omp_get_thread_num());
                }
            }

            #pragma omp taskwait

            printf("All tasks completed!\n");
        }
    }

    return 0;
}
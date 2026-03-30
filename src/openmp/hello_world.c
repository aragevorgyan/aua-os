#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main()
{
    
    #pragma omp parallel num_threads(8)
    {
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        //sleep(1);
        printf("world(%d)\n", ID);
    }
    sleep(1);
    #pragma omp parallel num_threads(2)
    {
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        printf("world(%d)\n", ID);
    }

    return 0;
}
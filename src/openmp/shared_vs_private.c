#include <stdio.h>
#include <omp.h>

int main(void) {
    int A[8] = {0};
    int B = 100;
    int C = 0;
    int id;   // will be private inside parallel region

    #pragma omp parallel shared(A, B, C) private(id)
    {
        id = omp_get_thread_num();

        /* A is shared: all threads access the same array */
        A[id] = id * 10;

        /* B is shared: all threads see the same value */
        printf("Thread %d sees B = %d\n", id, B);

        /* id is private: each thread has its own copy */
        printf("Thread %d has private id = %d\n", id, id);

        /* C is shared: all threads update the same variable */
        C = C + 1;   // race condition, only for demonstration
    }

    printf("\nFinal values:\n");

    printf("A: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("B = %d\n", B);
    printf("C = %d\n", C);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (1<<20)     // 1M elements (~4MB)
#define REPEAT 200    // amplify work

static double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

void predictable_branch(int *a) {
    long sum = 0;
    for (int r = 0; r < REPEAT; r++)
        for (int i = 0; i < N; i++)
            if (a[i] >= 0)   // always true
                sum += a[i];
    printf("predictable sum: %ld\n", sum);
}

void random_branch(int *a) {
    long sum = 0;
    for (int r = 0; r < REPEAT; r++)
        for (int i = 0; i < N; i++)
            if (a[i] & 1)    // random pattern
                sum += a[i];
    printf("random sum: %ld\n", sum);
}

void branchless(int *a) {
    long sum = 0;
    for (int r = 0; r < REPEAT; r++)
        for (int i = 0; i < N; i++)
            sum += a[i] * (a[i] & 1);  // no branch
    printf("branchless sum: %ld\n", sum);
}

int main() {

    int *a = malloc(sizeof(int) * N);

    // predictable case
    for (int i = 0; i < N; i++)
        a[i] = i;   // all >= 0

    double t1 = now();
    predictable_branch(a);
    double t2 = now();

    // random case
    srand(1);
    for (int i = 0; i < N; i++)
        a[i] = rand();

    double t3 = now();
    random_branch(a);
    double t4 = now();

    double t5 = now();
    branchless(a);
    double t6 = now();

    printf("\nPredictable branch time: %f sec\n", t2 - t1);
    printf("Random branch time:      %f sec\n", t4 - t3);
    printf("Branchless time:         %f sec\n", t6 - t5);

    free(a);
}
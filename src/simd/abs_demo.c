#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 200000000

static double now_sec(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

/* Version A: branch in the loop */
void abs_branch(float *a, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] < 0.0f)
            a[i] = -a[i];
    }
}

/* Version B: branchless */
void abs_fabs(float *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = fabsf(a[i]);
    }
}

int main(void) {
    float *x = malloc((size_t)N * sizeof(float));
    float *y = malloc((size_t)N * sizeof(float));
    if (!x || !y) { puts("alloc failed"); return 1; }

    // Make a predictable mix: half negative, half positive
    // for (int i = 0; i < N; i++) {
    //     float v = (i & 1) ? (float)i : -(float)i;
    //     x[i] = v;
    //     y[i] = v;
    // }

    srand(1);
    for (int i = 0; i < N; i++) {
        float v = (rand() & 1) ? (float)i : -(float)i;
        x[i] = v;
        y[i] = v;
    }

    double t1 = now_sec();
    abs_branch(x, N);
    double t2 = now_sec();

    double t3 = now_sec();
    abs_fabs(y, N);
    double t4 = now_sec();

    // Prevent dead-code elimination + sanity check
    printf("x[123]=%f  y[123]=%f\n", x[123], y[123]);
    printf("branch time:   %f sec\n", t2 - t1);
    printf("branchless time:%f sec\n", t4 - t3);

    free(x);
    free(y);
    return 0;
}
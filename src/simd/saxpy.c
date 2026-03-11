#include <stdio.h>
#include <stdlib.h>

#define N 100000000

void saxpy(float a, float *x, float *y) {
    for (int i = 0; i < N; i++) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    float *x = malloc(N * sizeof(float));
    float *y = malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    saxpy(3.0f, x, y);

    printf("y[0] = %f\n", y[0]);

    free(x);
    free(y);
}
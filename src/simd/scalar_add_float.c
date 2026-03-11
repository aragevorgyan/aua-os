#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000000

void scalar_add(float *a, float *b, float *result) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    float *a = (float*)malloc(sizeof(float) * SIZE);
    float *b = (float*)malloc(sizeof(float) * SIZE);
    float *result = (float*)malloc(sizeof(float) * SIZE);
    if (!a || !b || !result) return 1;

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = i * 1.0f;
        b[i] = (SIZE - i) * 1.0f;
    }

    // Measure scalar addition
    clock_t start = clock();
    scalar_add(a, b, result);
    clock_t end = clock();

    printf("Scalar Addition Time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(a); free(b); free(result);
    return 0;
}

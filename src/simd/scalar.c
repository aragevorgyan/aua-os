#include <stdio.h>
#include <time.h>

#define SIZE 1000000000

void scalar_add(float *a, float *b, float *result) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    float a[SIZE], b[SIZE], result[SIZE];

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

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define N 80000000   // keep multiple of 8

double scalar_dot(const float *a, const float *b) {
    double sum = 0.0;
    for (int i = 0; i < N; i++)
        sum += (double)a[i] * (double)b[i];
    return sum;
}

double simd_dot(const float *a, const float *b) {
    __m256 sum = _mm256_setzero_ps();

    for (int i = 0; i < N; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        sum = _mm256_add_ps(sum, _mm256_mul_ps(va, vb));
    }

    float tmp[8];
    _mm256_storeu_ps(tmp, sum);

    double final = 0.0;
    for (int i = 0; i < 8; i++)
        final += (double)tmp[i];

    return final;
}

double now() { return (double)clock() / CLOCKS_PER_SEC; }

int main() {
    float *a = malloc(sizeof(float) * N);
    float *b = malloc(sizeof(float) * N);

    for (int i = 0; i < N; i++) { a[i] = 1.0f; b[i] = 2.0f; }

    double t1 = now();
    double s1 = scalar_dot(a, b);
    double t2 = now();

    double t3 = now();
    double s2 = simd_dot(a, b);
    double t4 = now();

    printf("Scalar result: %.0f\n", s1);
    printf("SIMD result:   %.0f\n\n", s2);

    printf("Scalar time: %f sec\n", t2 - t1);
    printf("SIMD time:   %f sec\n", t4 - t3);

    free(a); free(b);
    return 0;
}
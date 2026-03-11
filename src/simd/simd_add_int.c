#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define SIZE 1000000000

void simd_add_i32(const int32_t *a, const int32_t *b, int32_t *r, size_t n) {
    int i;
    for (i = 0; i + 8 <= n; i += 8) {
        __m256i va = _mm256_loadu_si256((const __m256i*)(a + i));
        __m256i vb = _mm256_loadu_si256((const __m256i*)(b + i));
        __m256i vr = _mm256_add_epi32(va, vb);
        _mm256_storeu_si256((__m256i*)(r + i), vr);
    }
    for (; i < n; i++) r[i] = a[i] + b[i];
}

int main(void) {
    int32_t *a = (int32_t*)malloc(sizeof(int32_t) * SIZE);
    int32_t *b = (int32_t*)malloc(sizeof(int32_t) * SIZE);
    int32_t *r = (int32_t*)malloc(sizeof(int32_t) * SIZE);
    if (!a || !b || !r) return 1;

    for (size_t i = 0; i < SIZE; i++) {
        a[i] = (int32_t)i;
        b[i] = (int32_t)(SIZE - i);
    }

    clock_t start = clock();
    simd_add_i32(a, b, r, SIZE);
    clock_t end = clock();

    printf("AVX2 int32 add time: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("r[0]=%d r[last]=%d\n", r[0], r[SIZE-1]);

    free(a); free(b); free(r);
    return 0;
}
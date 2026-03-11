#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

static uint64_t count_A_scalar(const unsigned char *buf, size_t n) {
    uint64_t cnt = 0;
    for (size_t i = 0; i < n; i++) {
        cnt += (buf[i] == (unsigned char)'A');
    }
    return cnt;
}

static uint64_t count_A_avx2(const unsigned char *buf, size_t n) {
    uint64_t cnt = 0;

    const __m256i target = _mm256_set1_epi8('A');

    size_t i = 0;
    size_t limit = n & ~(size_t)31;  // round down to multiple of 32

    for (; i < limit; i += 32) {
        __m256i v = _mm256_loadu_si256((const __m256i*)(buf + i));
        __m256i eq = _mm256_cmpeq_epi8(v, target);

        // Each bit in mask corresponds to one byte match
        unsigned mask = (unsigned)_mm256_movemask_epi8(eq);

        // Count set bits = number of matches in these 32 bytes
        cnt += (uint64_t)__builtin_popcount(mask);
    }

    // Tail
    for (; i < n; i++) {
        cnt += (buf[i] == (unsigned char)'A');
    }

    return cnt;
}

int main(void) {
    // Size of buffer
    const size_t N = (size_t)1024 * 1024 * 1024;

    unsigned char *buf = (unsigned char*)malloc(N);
    if (!buf) {
        perror("malloc");
        return 1;
    }

    // Fill with random-ish data and inject some 'A's
    srand(1);
    for (size_t i = 0; i < N; i++) {
        unsigned r = (unsigned)rand();
        buf[i] = (unsigned char)(r & 0xFF);
        if ((r & 1023u) == 0u) buf[i] = (unsigned char)'A';  // ~0.1% A's
    }

    // Warmup (optional): touch memory so first timing isn't "cold page faults"
    // volatile unsigned char sink = 0;
    // for (size_t i = 0; i < N; i += 4096) sink ^= buf[i];
    // (void)sink;

    double t1 = now_sec();
    uint64_t c1 = count_A_scalar(buf, N);
    double t2 = now_sec();

    double t3 = now_sec();
    uint64_t c2 = count_A_avx2(buf, N);
    double t4 = now_sec();

    printf("Scalar count: %llu\n", (unsigned long long)c1);
    printf("SIMD   count: %llu\n\n", (unsigned long long)c2);

    printf("Scalar time: %f sec\n", t2 - t1);
    printf("SIMD time:   %f sec\n", t4 - t3);

    free(buf);
    return 0;
}
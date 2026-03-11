#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 30000

// 30000 * 30000 * 4 bytes = 3.6 GB > 256 MB (L3 cache size) => cache miss
int matrix[N][N];

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main() {

    // Initialize matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = i + j;

    long long sum = 0;

    // ========================
    // Row-wise traversal
    // ========================
    double start = get_time();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += matrix[i][j];

    double end = get_time();
    printf("Row traversal time: %f seconds\n", end - start);

    // Prevent optimization
    printf("Sum: %lld\n", sum);

    sum = 0;

    // ========================
    // Column-wise traversal
    // ========================
    start = get_time();

    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            sum += matrix[i][j];

    end = get_time();
    printf("Column traversal time: %f seconds\n", end - start);

    printf("Sum: %lld\n", sum);

    return 0;
}
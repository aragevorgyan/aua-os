#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE (64 * 1024 * 1024)

int arr[ARRAY_SIZE];

// Function to get current time in seconds
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    // Initialize array with some values (e.g., 1)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = 1;
    }

    // Measure time for Loop 1 (every element)
    // double start_time = get_time();
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     arr[i] *= 3;
    // }
    // double end_time = get_time();
    // printf("Loop 1 time: %.6f seconds\n", end_time - start_time);

    // Re-initialize array to avoid interference with the second loop
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     arr[i] = 1;
    // }

    // Measure time for Loop 2 (every 16th element)
    double start_time = get_time();
    for (int i = 0; i < ARRAY_SIZE; i += 2) {
        arr[i] *= 3;
    }
    double end_time = get_time();
    printf("Loop 2 time: %.6f seconds\n", end_time - start_time);

    return 0;
}
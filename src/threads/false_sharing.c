#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 2
#define NUM_ITERATIONS 100000000

typedef struct {
    int value1;
    int value2; 
} SharedData;

typedef struct {
    int value1;
    char padding[64];
    int value2;
} PaddedData;

SharedData shared_data = {0, 0};
PaddedData padded_data = {0, {0}, 0};

void *increment_shared_value1(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        shared_data.value1++;
    }
    return NULL;
}

void *increment_shared_value2(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        shared_data.value2++;
    }
    return NULL;
}

void *increment_padded_value1(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        padded_data.value1++;
    }
    return NULL;
}

void *increment_padded_value2(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        padded_data.value2++;
    }
    return NULL;
}

double measure_execution_time(void *(*func1)(void *), void *(*func2)(void *)) {
    pthread_t threads[NUM_THREADS];
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&threads[0], NULL, func1, NULL);
    pthread_create(&threads[1], NULL, func2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_nsec - start.tv_nsec) / 1e9;
    return elapsed_time;
}

int main() {
    double time_with_false_sharing = measure_execution_time(increment_shared_value1, increment_shared_value2);
    printf("Time with false sharing: %.6f seconds\n", time_with_false_sharing);

    double time_without_false_sharing = measure_execution_time(increment_padded_value1, increment_padded_value2);
    printf("Time without false sharing: %.6f seconds\n", time_without_false_sharing);

    return 0;
}

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
} MyStruct;

MyStruct my_data = {0, 0};


void *increment_mystruct_value1(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        my_data.value1++;
    }
    return NULL;
}

void *increment_mystruct_value2(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        my_data.value2++;
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
    double time_with_false_sharing = measure_execution_time(increment_mystruct_value1, increment_mystruct_value2);
    printf("Time : %.6f seconds\n", time_with_false_sharing);

    return 0;
}

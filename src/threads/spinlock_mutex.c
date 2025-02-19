#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 10000000

long long counter = 0;           // Shared counter
pthread_mutex_t mutex;           // Mutex
pthread_spinlock_t spinlock;     // Spinlock

// Thread function for incrementing with a mutex
void* increment_with_mutex(void* arg) {
    for (long long i = 0; i < NUM_INCREMENTS / NUM_THREADS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Thread function for incrementing with a spinlock
void* increment_with_spinlock(void* arg) {
    for (long long i = 0; i < NUM_INCREMENTS / NUM_THREADS; i++) {
        pthread_spin_lock(&spinlock);
        counter++;
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}

// Function to measure execution time of a synchronization method
double measure_execution_time(void* (*thread_func)(void*)) {
    pthread_t threads[NUM_THREADS];
    struct timeval start, end;

    // Record start time
    gettimeofday(&start, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record end time
    gettimeofday(&end, NULL);

    // Calculate execution time in milliseconds
    double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;
    execution_time += (end.tv_usec - start.tv_usec) / 1000.0;

    return execution_time;
}

int main() {
    // Initialize mutex and spinlock
    pthread_mutex_init(&mutex, NULL);
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    printf("Testing with %d threads, %d increments.\n", NUM_THREADS, NUM_INCREMENTS);

    // Test with mutex
    counter = 0;  // Reset counter
    double mutex_time = measure_execution_time(increment_with_mutex);
    printf("Mutex Time: %.2f ms, Final Counter: %lld\n", mutex_time, counter);

    // Test with spinlock
    counter = 0;  // Reset counter
    double spinlock_time = measure_execution_time(increment_with_spinlock);
    printf("Spinlock Time: %.2f ms, Final Counter: %lld\n", spinlock_time, counter);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_spin_destroy(&spinlock);

    return 0;
}

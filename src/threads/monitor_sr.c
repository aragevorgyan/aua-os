#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep

#define NUM_THREADS 5

// Monitor structure
typedef struct {
    pthread_mutex_t mutex;         // Mutex for mutual exclusion
    pthread_cond_t resource_free;  // Condition variable to signal resource availability
    int is_resource_busy;          // State of the resource (0 = free, 1 = busy)
} Monitor;

// Monitor initialization function
void init_monitor(Monitor *m) {
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->resource_free, NULL);
    m->is_resource_busy = 0;
}

// Monitor destroy function
void destroy_monitor(Monitor *m) {
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->resource_free);
}

// Function to acquire the resource
void acquire_resource(Monitor *m, int tid) {
    pthread_mutex_lock(&m->mutex);
    while (m->is_resource_busy) {
        printf("Thread %d: Waiting for the resource to become available...\n", tid);
        pthread_cond_wait(&m->resource_free, &m->mutex);
    }
    m->is_resource_busy = 1;  // Mark the resource as busy
    printf("Thread %d: Acquired the resource.\n", tid);
    pthread_mutex_unlock(&m->mutex);
}

// Function to release the resource
void release_resource(Monitor *m, int tid) {
    pthread_mutex_lock(&m->mutex);
    m->is_resource_busy = 0;  // Mark the resource as free
    printf("Thread %d: Released the resource.\n", tid);
    pthread_cond_signal(&m->resource_free);  // Signal waiting threads
    pthread_mutex_unlock(&m->mutex);
}

// Thread function to simulate resource usage
void *use_resource(void *arg) {
    int tid = *(int *)arg;
    extern Monitor monitor;

    acquire_resource(&monitor, tid);

    // Simulate resource usage
    sleep(1);

    release_resource(&monitor, tid);

    pthread_exit(NULL);
}

// Global monitor
Monitor monitor;

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    // Initialize the monitor
    init_monitor(&monitor);

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, use_resource, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the monitor
    destroy_monitor(&monitor);

    printf("All threads have finished.\n");
    return 0;
}

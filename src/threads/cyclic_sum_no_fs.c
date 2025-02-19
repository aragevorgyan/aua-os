#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>  // For CPU_SET, CPU_ZERO, pthread_setaffinity_np


#define ARRAY_SIZE 100000000
#define MAX_THREADS 4
#define CACHE_LINE_SIZE 64

int array[ARRAY_SIZE];

// Pad sum array to prevent false sharing
long sum[MAX_THREADS][CACHE_LINE_SIZE / sizeof(long)];

void* thread_sum(void* arg) {
    int thread_id = *(int*)arg;
    int num_threads = *(int*)(arg + sizeof(int)); // Retrieve dynamic thread count
    
    // Set CPU affinity: bind thread to a specific CPU
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(thread_id, &cpuset);  // Bind the thread to CPU 'thread_id' (0, 1, 2, 3)
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

    long local_sum = 0;
    for (int i = thread_id; i < ARRAY_SIZE; i += num_threads) {
        local_sum += array[i];  // Leapfrog access pattern
    }
    
    // Store the result in the padded sum array
    sum[thread_id][0] = local_sum;
    return NULL;
}

double run_test(int num_threads) {
    pthread_t threads[MAX_THREADS];
    int thread_data[MAX_THREADS][2]; // Store thread ID and num_threads
    long total_sum = 0;
    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_data[i][0] = i;
        thread_data[i][1] = num_threads; // Pass dynamic thread count
        pthread_create(&threads[i], NULL, thread_sum, &thread_data[i]);
    }

    // Wait for threads and collect results
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += sum[i][0];
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Threads: %d | Time: %.6f sec | Total Sum: %ld\n", num_threads, elapsed_time, total_sum);
    return elapsed_time;
}

int main() {
    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1;  // Simple case: sum should be ARRAY_SIZE
    }

    printf("Demonstration (Cyclic Distribution):\n");
    for (int threads = 1; threads <= MAX_THREADS; threads++) {
        run_test(threads);
    }

    return 0;
}

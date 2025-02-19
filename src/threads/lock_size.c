#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 100           // Number of threads
#define NUM_OPERATIONS 10000000  // Number of operations each thread will perform

long long counter1 = 0, counter2 = 0;  // Two counters
pthread_mutex_t lock1, lock2;           // Locks for fine-grained locking
pthread_mutex_t coarse_lock;            // Lock for coarse-grained locking

// Function to update both counters with coarse-grained locking
void* update_counters_coarse_grained(void* arg) {
    for (long long i = 0; i < NUM_OPERATIONS / NUM_THREADS; i++) {
        pthread_mutex_lock(&coarse_lock);
        counter1++;
        counter2++;
        pthread_mutex_unlock(&coarse_lock);
    }
    return NULL;
}

// Function to update both counters with fine-grained locking
void* update_counters_fine_grained(void* arg) {
    for (long long i = 0; i < NUM_OPERATIONS / NUM_THREADS; i++) {
        pthread_mutex_lock(&lock1);
        counter1++;
        pthread_mutex_unlock(&lock1);
        
        pthread_mutex_lock(&lock2);
        counter2++;
        pthread_mutex_unlock(&lock2);
    }
    return NULL;
}

// Function to measure the execution time of a given thread function
double measure_execution_time(void* (*thread_func)(void*)) {
    pthread_t threads[NUM_THREADS];
    struct timeval start, end;

    gettimeofday(&start, NULL);  // Record start time
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);  // Create threads
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);  // Join threads
    }

    gettimeofday(&end, NULL);  // Record end time

    double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;  // Calculate time in ms
    execution_time += (end.tv_usec - start.tv_usec) / 1000.0;

    return execution_time;
}

int main() {
    // Initialize locks
    pthread_mutex_init(&coarse_lock, NULL);
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Test with coarse-grained locking
    counter1 = 0;
    counter2 = 0;
    double coarse_grained_time = measure_execution_time(update_counters_coarse_grained);
    printf("Coarse-grained Locking Time: %.2f ms, Final Counter1: %lld, Counter2: %lld\n",
           coarse_grained_time, counter1, counter2);

    // Test with fine-grained locking
    counter1 = 0;
    counter2 = 0;
    double fine_grained_time = measure_execution_time(update_counters_fine_grained);
    printf("Fine-grained Locking Time: %.2f ms, Final Counter1: %lld, Counter2: %lld\n",
           fine_grained_time, counter1, counter2);

    // Destroy locks
    pthread_mutex_destroy(&coarse_lock);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}

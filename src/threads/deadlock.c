#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thread1_func(void* arg) {
    printf("Thread 1: Attempting to lock mutex 1\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 1: Locked mutex 1\n");

    // Simulate some work
    sleep(1);

    printf("Thread 1: Attempting to lock mutex 2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 1: Locked mutex 2\n");

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    printf("Thread 1: Released both mutexes\n");
    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2: Attempting to lock mutex 2\n");
    pthread_mutex_lock(&lock2);
    printf("Thread 2: Locked mutex 2\n");

    // Simulate some work
    sleep(1);

    printf("Thread 2: Attempting to lock mutex 1\n");
    pthread_mutex_lock(&lock1);
    printf("Thread 2: Locked mutex 1\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    printf("Thread 2: Released both mutexes\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutexes
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Create the threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutexes
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("Main: Program completed.\n");
    return 0;
}

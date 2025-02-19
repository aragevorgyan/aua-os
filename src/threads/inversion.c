#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

void* low_priority_thread(void* arg) {
    printf("Low-priority thread: Locking the resource.\n");
    pthread_mutex_lock(&lock);

    printf("Low-priority thread: Working...\n");
    sleep(5); // Simulate work

    printf("Low-priority thread: Unlocking the resource.\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* high_priority_thread(void* arg) {
    printf("High-priority thread: Waiting for the resource.\n");
    pthread_mutex_lock(&lock);

    printf("High-priority thread: Acquired the resource!\n");
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* medium_priority_thread(void* arg) {
    printf("Medium-priority thread: Doing work...\n");
    sleep(3); // Simulate work that preempts low-priority thread
    printf("Medium-priority thread: Finished work.\n");

    return NULL;
}

int main() {
    pthread_t low, medium, high;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    pthread_create(&low, NULL, low_priority_thread, NULL);
    sleep(1); // Ensure low-priority thread locks the resource first

    pthread_create(&high, NULL, high_priority_thread, NULL);
    sleep(1); // Allow high-priority thread to start waiting

    pthread_create(&medium, NULL, medium_priority_thread, NULL);

    // Wait for threads to finish
    pthread_join(low, NULL);
    pthread_join(medium, NULL);
    pthread_join(high, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Main: All threads finished.\n");
    return 0;
}

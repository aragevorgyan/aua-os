#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by the thread
void* thread_function(void* arg) {
    printf("Hello from thread!\n");
    while(1) {
        printf("Hello from thread loop!\n");
    }
    return NULL;
}

int main() {
    pthread_t thread_1;
    pthread_t thread_2;

    // Create a new thread
    if (pthread_create(&thread_1, NULL, thread_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread_2, NULL, thread_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    printf("Thread created, waiting for it to finish...\n");
    while(1) {
        printf("Inside main\n");
    }

    // Wait for the thread to complete
    if (pthread_join(thread_1, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    if (pthread_join(thread_2, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("A finished!\n");
    return 0;
}

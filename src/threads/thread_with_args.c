#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// A struct to hold the arguments for the thread
typedef struct {
    int thread_id;
    char* message;
} thread_data_t;

// Thread function to print the thread's ID and message
void* print_thread_info(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    printf("Thread ID: %d, Message: %s\n", data->thread_id, data->message);
    return NULL;
}

int main() {
    pthread_t thread;
    thread_data_t thread_data;

    // Initialize the thread data
    thread_data.thread_id = 1;
    thread_data.message = "Hello from the thread!";

    // Create the thread, passing a pointer to thread_data as the argument
    if (pthread_create(&thread, NULL, print_thread_info, (void*)&thread_data) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    printf("Main thread finished\n");
    return 0;
}

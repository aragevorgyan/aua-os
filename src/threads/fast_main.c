#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* worker(void* arg) {
    printf("Worker thread started!\n");
    sleep(2);
    printf("Worker thread finished!\n");
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, worker, NULL);
    
    printf("Main thread exiting...\n");
    // No pthread_join() here!
    return 0;
}

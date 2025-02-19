#define _GNU_SOURCE  // Enable GNU extensions
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

void* thread_func(void* arg) {
    printf("Thread %ld running on CPU %d\n", (long)arg, sched_getcpu());
    return NULL;
}

int main() {
    pthread_t threads[8];

    for (long i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

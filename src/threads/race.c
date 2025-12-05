#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>

int x = 5;

void tiny_delay(void) {
    for (volatile int k = 0; k < 100000; ++k) { /* spin */ }
}

void* increment(void* arg) {
    tiny_delay();
    x++;
    //printf("Inc\n");
    return NULL;
}

void* decrement(void* arg) {
    tiny_delay();
    x--;
    //printf("Dec\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    for(int i = 0; i < 20000; i++)
    {
        x = 5;
        // Create threads
        pthread_create(&tid1, NULL, increment, NULL);
        pthread_create(&tid2, NULL, decrement, NULL);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        if(x != 5)
            printf("Final value of x: %d\n", x);
    }

    return 0;
}

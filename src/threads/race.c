#include <pthread.h>
#include <stdio.h>

int x = 5;

void* increment(void* arg) {
        x++;
    return NULL;
}

void* decrement(void* arg) {
        x--;
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    for(int i = 0; i < 10; i++)
    {
        x = 5;
        // Create threads
        pthread_create(&tid1, NULL, increment, NULL);
        pthread_create(&tid2, NULL, decrement, NULL);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        printf("Final value of x: %d\n", x);
    }


    return 0;
}

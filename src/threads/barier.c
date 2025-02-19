#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 9
#define BARIER_NUM 3
pthread_barrier_t barrier;

void* routine(void* args) {
    printf("Waiting at the barrier...\n");
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier\n");
}

int main(int argc, char *argv[]) {
	pthread_t th[THREAD_NUM];
	int i;
    pthread_barrier_init(&barrier, NULL, BARIER_NUM);
	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Failed to create thread");
		}
	}
	for (i = 0; i < THREAD_NUM; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
    pthread_barrier_destroy(&barrier);
	return 0;
}
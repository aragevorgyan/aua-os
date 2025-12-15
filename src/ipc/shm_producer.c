// writer.c - writes an integer into shared memory and signals via semaphore
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // O_* constants
#include <sys/mman.h>   // shm_open, mmap
#include <sys/stat.h>   // mode constants
#include <unistd.h>     // ftruncate, close
#include <semaphore.h>  // sem_t, sem_open, sem_post, sem_close

#define SHM_NAME "/simple_shm"
#define SEM_NAME "/simple_sem"

int main(void) {
    int fd;
    int *ptr;
    sem_t *sem;

    // 1. Create or open shared memory
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 2. Set size for one int
    if (ftruncate(fd, sizeof(int)) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3. Map shared memory
    ptr = mmap(NULL, sizeof(int),
               PROT_READ | PROT_WRITE,
               MAP_SHARED,
               fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 4. Create or open named semaphore, initial value = 0
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        munmap(ptr, sizeof(int));
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 5. Get input and write to shared memory
    int value;
    printf("Writer: enter an integer: ");
    fflush(stdout);
    if (scanf("%d", &value) != 1) {
        fprintf(stderr, "Writer: invalid input\n");
        sem_close(sem);
        munmap(ptr, sizeof(int));
        close(fd);
        exit(EXIT_FAILURE);
    }

    *ptr = value;
    printf("Writer: wrote %d to shared memory\n", value);

    // 6. Signal reader that data is ready
    if (sem_post(sem) == -1) {
        perror("sem_post");
    }

    // 7. Cleanup local handles (do not unlink here, let reader do it)
    sem_close(sem);
    munmap(ptr, sizeof(int));
    close(fd);

    return 0;
}

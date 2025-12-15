// reader.c - waits on semaphore, then reads integer from shared memory
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // O_* constants
#include <sys/mman.h>   // shm_open, mmap
#include <sys/stat.h>   // mode constants
#include <unistd.h>     // close
#include <semaphore.h>  // sem_t, sem_open, sem_wait, sem_close, sem_unlink

#define SHM_NAME "/simple_shm"
#define SEM_NAME "/simple_sem"

int main(void) {
    int fd;
    int *ptr;
    sem_t *sem;

    // 1. Open existing shared memory
    fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // 2. Map it
    ptr = mmap(NULL, sizeof(int),
               PROT_READ | PROT_WRITE,
               MAP_SHARED,
               fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3. Open existing semaphore
    sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        munmap(ptr, sizeof(int));
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 4. Wait for writer to post
    printf("Reader: waiting for data...\n");
    if (sem_wait(sem) == -1) {
        perror("sem_wait");
        sem_close(sem);
        munmap(ptr, sizeof(int));
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 5. Now safe to read
    printf("Reader: value in shared memory = %d\n", *ptr);

    // 6. Cleanup: close and unlink shared objects
    sem_close(sem);
    munmap(ptr, sizeof(int));
    close(fd);

    // Remove semaphore and shared memory from the system
    sem_unlink(SEM_NAME);
    shm_unlink(SHM_NAME);

    return 0;
}

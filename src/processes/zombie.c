#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Child process exiting.\n");
        exit(0); // Exit immediately
    } else {
        // Parent process
        printf("Parent sleeping for 20 seconds.\n");
        sleep(20); // Delay to allow child to exit and become a zombie
        printf("Parent waking up and waiting for child.\n");
        wait(NULL); // Wait for child to exit
    }

    return 0;
}
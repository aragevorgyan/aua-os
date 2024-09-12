#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    
    pid = fork(); // Create a new process
    
    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // Simulate some work in the child process
        printf("Child process finished.\n");

        exit(0); // End child process
    } else {
        // Parent process
        printf("Parent process: Waiting for child to finish...\n");
        wait(NULL); // Wait for the child process to finish
        printf("Parent process: Child has finished.\n");
    }
    
    return 0;
}
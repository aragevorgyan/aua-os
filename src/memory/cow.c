#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100;

    printf("Parent: Initial value of x = %d\n", x);

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child: Before modifying x, value of x = %d\n", x);
        x = 200;  // Modify the variable in the child process
        printf("Child: After modifying x, value of x = %d\n", x);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child process to finish
        printf("Parent: After child process, value of x = %d\n", x);
    }

    return 0;
}

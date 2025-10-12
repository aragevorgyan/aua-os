#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 42;

    printf("Parent: Initial value of x = %d\n", x);
    printf("Parent: Initial addr of x = %p\n", &x);

    // Fork a child process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child: Before modifying x, value of x = %d\n", x);
        printf("Child: Before modifying x, addr of x = %p\n", &x);
        x = 200; // Modify the variable in the child process
        printf("Child: After modifying x, value of x = %d\n", x);
        printf("Child: After modifying x, addr of x = %p\n", &x);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child process to finish
        //x = 256;
        printf("Parent: After modifying x, value of x = %d\n", x);
        printf("Parent: After child process, addr of x = %p\n", &x);
    }

    return 0;
}

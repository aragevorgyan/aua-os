#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 42;

int main() {
    printf("Parent PID: %d, value=%d, addr=%p\n", getpid(), value, &value);

    pid_t pid = fork();
    if (pid == 0) {
        // Child
        printf("Child before write: value=%d, addr=%p\n", value, &value);
        value = 99;  // triggers COW
        printf("Child after write:  value=%d, addr=%p\n", value, &value);
        exit(0);
    } else {
        wait(NULL);
        printf("Parent after child exit: value=%d, addr=%p\n", value, &value);
    }
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2];
    int value;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // ----- CHILD PROCESS -----
        close(fd[1]);  // Close write end

        int received;
        read(fd[0], &received, sizeof(int));

        printf("Child received integer: %d\n", received);

        close(fd[0]);
    } else {
        // ----- PARENT PROCESS -----
        close(fd[0]);  // Close read end

        printf("Enter an integer: ");
        //fflush(stdout);
        scanf("%d", &value);

        write(fd[1], &value, sizeof(int));

        close(fd[1]);
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd[2];
    char buffer[100];

    // Create the pipe
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
        // --- CHILD PROCESS ---
        close(fd[1]);  // Close unused write end

        // Read from pipe
        int n = read(fd[0], buffer, sizeof(buffer));
        buffer[n] = '\0'; // Null-terminate

        printf("Child received: %s\n", buffer);

        close(fd[0]); // Close read end
    } 
    else {
        // --- PARENT PROCESS ---
        close(fd[0]); // Close unused read end

        const char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));

        close(fd[1]); // Closing this sends EOF to child
    }

    return 0;
}

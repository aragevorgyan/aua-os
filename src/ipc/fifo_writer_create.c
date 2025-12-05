#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"

int main() {
    // Create FIFO if it doesn’t already exist
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        // If FIFO already exists, ignore the error
    }

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char msg[] = "Hello from C-created FIFO!";
    write(fd, msg, sizeof(msg));

    printf("Writer: sent message.\n");
    close(fd);

    return 0;
}

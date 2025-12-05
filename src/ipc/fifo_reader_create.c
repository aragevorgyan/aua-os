#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_PATH "myfifo"

int main() {
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buffer[100];
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';

    printf("Reader: received -> %s\n", buffer);

    close(fd);

    return 0;
}

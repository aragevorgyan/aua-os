#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char msg[] = "Hello through FIFO!";
    write(fd, msg, sizeof(msg));
    close(fd);
}

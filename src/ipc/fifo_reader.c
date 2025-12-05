#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buffer[100];
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    close(fd);
}

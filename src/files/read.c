#include <stdio.h>
#include <fcntl.h>    // For open()
#include <unistd.h>   // For read(), close()
#include <stdlib.h>   // For exit()

int main() {
    int fd;
    char buffer[100];
    ssize_t bytesRead;

    // Open an existing file for reading
    fd = open("demo.txt", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Read up to 100 bytes
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate and print what was read
    buffer[bytesRead] = '\0';
    printf("Read %zd bytes: \"%s\"\n", bytesRead, buffer);

    // Always close the file
    close(fd);
    return 0;
}

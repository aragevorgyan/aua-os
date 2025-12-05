#include <stdio.h>
#include <fcntl.h>    // For creat()
#include <unistd.h>   // For close()
#include <stdlib.h>   // For exit()

int main() {
    int fd;

    // Create a new file "demo.txt" with read/write permissions for the owner
    fd = creat("demo.txt", 0644);
    if (fd == -1) {
        perror("creat failed");
        exit(EXIT_FAILURE);
    }

    printf("File created successfully with file descriptor: %d\n", fd);

    // Always close the file descriptor
    close(fd);
    return 0;
}

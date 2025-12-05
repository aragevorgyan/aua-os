#include <stdio.h>
#include <unistd.h>   // for read()
#include <string.h>   // for strlen()
#include <stdlib.h>   // for atoi()

int main(void) {
    char buffer[100];        // buffer to hold user input
    int bytes_read;

    // Prompt the user
    write(1, "Enter a number: ", strlen("Enter a number: "));  // fd 1 = stdout

    // Read from stdin (fd 0)
    bytes_read = read(0, buffer, sizeof(buffer) - 1);

    if (bytes_read < 0) {
        perror("read failed");
        return 1;
    }

    buffer[bytes_read] = '\0';   // null-terminate the string

    // Convert to integer (like scanf("%d", &x))
    int num = atoi(buffer);

    // Print it back
    char out[100];
    snprintf(out, sizeof(out), "You entered: %d\n", num);
    write(1, out, strlen(out));   // fd 1 = stdout

    return 0;
}

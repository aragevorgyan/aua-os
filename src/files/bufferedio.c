#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int ch;

    // ---------- Unbuffered read() ----------
    int fd = open("input.txt", O_RDONLY);

    printf("Unbuffered read()...\n");
    while (read(fd, &ch, 1) == 1) {
        // do something
    }
    close(fd);

    // ---------- Buffered fgetc() ----------
    FILE *fp = fopen("input.txt", "r");

    printf("Buffered fgetc()...\n");
    while ((ch = fgetc(fp)) != EOF) {
        // do something
    }
    fclose(fp);

    return 0;
}

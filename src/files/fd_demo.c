#include <stdio.h>
#include <unistd.h>

int main() {
    write(1, "This is standard output (fd 1)\n", 32);
    write(2, "This is standard error (fd 2)\n", 31);

    char buf[50];
    write(1, "Type something: ", 16);
    int n = read(0, buf, sizeof(buf));  // Read from stdin
    write(1, "You typed: ", 11);
    write(1, buf, n);                   // Echo input

    return 0;
}

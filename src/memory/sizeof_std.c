#include <stdio.h>

int main() {

    int intVar;
    float floatVar;
    double doubleVar;
    char charVar;
    size_t sizeVar;

    // Print the size of each type using sizeof
    printf("Size of int: %lu bytes\n", sizeof(intVar));
    printf("Size of float: %lu bytes\n", sizeof(floatVar));
    printf("Size of double: %lu bytes\n", sizeof(doubleVar));
    printf("Size of char: %lu byte\n", sizeof(charVar));
    printf("Size of size_t: %lu bytes\n", sizeof(sizeVar));

    return 0;
}

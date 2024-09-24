#include <stdio.h>

// Define a struct
struct DataHolder {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
    double d;    // 8 bytes
};

int main() {
    // Create an instance of the struct
    struct DataHolder example;

    // Print the sizes of the struct and its members
    printf("Size of char: %lu bytes\n", sizeof(char));
    printf("Size of int: %lu bytes\n", sizeof(int));
    printf("Size of double: %lu bytes\n", sizeof(double));
    printf("Size of DataHolder: %lu bytes\n", sizeof(struct DataHolder));

    // Calculate the offsets of each member
    printf("Offset of a: %lu bytes\n", (size_t)&example.a - (size_t)&example);
    printf("Offset of b: %lu bytes\n", (size_t)&example.b - (size_t)&example);
    printf("Offset of c: %lu bytes\n", (size_t)&example.c - (size_t)&example);
    printf("Offset of d: %lu bytes\n", (size_t)&example.d - (size_t)&example);

    return 0; // Exit successfully
}

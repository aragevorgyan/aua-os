#include <stdio.h>

// Define a struct
struct DataHolder {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
};

int main() {
    struct DataHolder example;

    // Print the size of the struct
    printf("Size of struct DataHolder: %lu bytes\n", sizeof(example));

    // Calculate and print the offsets of each member
    printf("Offset of a: %lu bytes\n", (size_t)&example.a - (size_t)&example);
    printf("Offset of b: %lu bytes\n", (size_t)&example.b - (size_t)&example);
    printf("Offset of c: %lu bytes\n", (size_t)&example.c - (size_t)&example);

    return 0; // Exit successfully
}

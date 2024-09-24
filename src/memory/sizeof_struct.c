#include <stdio.h>

// Define a struct to represent a point in 2D space
struct Point {
    int x;      // X coordinate
    int y;      // Y coordinate
};

int main() {
    // Declare a variable of type struct Point
    struct Point p1;

    // Initialize the struct members
    p1.x = 10;
    p1.y = 20;

    // Print the values of the struct
    printf("Point coordinates: (%d, %d)\n", p1.x, p1.y);

    // Use sizeof to determine the size of the struct
    printf("Size of struct Point: %lu bytes\n", sizeof(struct Point));
    printf("Size of x: %lu bytes\n", sizeof(p1.x));
    printf("Size of y: %lu bytes\n", sizeof(p1.y));

    return 0; // Exit successfully
}

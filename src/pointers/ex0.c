#include <stdio.h>

// Function that modifies the value of the argument
void modifyValue(int a) {
    int b;
    a = a + 10;
    printf("Value inside the function: %d\n", a);
}

int main() {
    int a = 5;

    printf("Value before calling the function: %d\n", a);

    modifyValue(a);

    printf("Value after calling the function: %d\n", a);

    return 0;
}
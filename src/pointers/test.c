#include <stdio.h>

int main()
{
    int x = 65535;
    int *ptr = &x;
    
    printf("val = %d\n", *(unsigned char *)ptr);
    printf("val = %d\n", *((unsigned char *)(ptr) + 1));
    printf("val = %d\n", *((unsigned char *)(ptr) + 2));
    printf("val = %d\n", *((unsigned char *)(ptr) + 3));
    return 0;
}
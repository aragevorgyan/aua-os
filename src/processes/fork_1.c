#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>

int main() 
{ 
    printf("Before fork\n");

	// make two process which run the same program after this instruction
	
	fork();

	printf("After fork!\n");
    while(1);

	return 0; 
} 

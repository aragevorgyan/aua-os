#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	int ret = fork();
	if (ret == 0)                     // child process because return value zero 
		printf("Hello from Child! ret:%d\n", ret); 
	else                              // parent process because return value non-zero. 
		printf("Hello from Parent! ret:%d\n", ret);	

	return 0; 
} 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

extern int errno;

int main()
{
    const char *buf = "My ship is strong!!!";
    ssize_t nr = 0;
    int fd;
    int ret;
    errno = 0;
    unsigned char c[4];
    off_t l_ret;

    fd = open("lseek_file.txt", O_RDWR);// | O_WRONLY | O_APPEND);// S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
    {
        perror("open");
    }

    nr = write(fd, buf, strlen(buf));
    if (nr == -1)
    {
        perror("write");
    }

    l_ret = lseek(fd, (off_t)-4, SEEK_END);

    nr = read(fd, c, 4);
    perror("read");
    printf("End of reading, nr = %ld\n", nr);
    printf("word = %s\n", c);


    if (close (fd) == -1)
        perror ("");
    
    return 0;
}
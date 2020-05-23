// simple_char_dev_test_read.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 128
#define DEV_NAME "/dev/simple_char_dev"

int main()
{
    char buffer[BUFFER_SIZE];
    int fd;

    fd = open(DEV_NAME, O_RDONLY);
    if (fd < 0)
    {
        printf("Open device %s failed\n", DEV_NAME);
        return EXIT_FAILURE;
    }

    read(fd, buffer, 64);
    printf("%s", buffer);

    close(fd);
    return 0;
}

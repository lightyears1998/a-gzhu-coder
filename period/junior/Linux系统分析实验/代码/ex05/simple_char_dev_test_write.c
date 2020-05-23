// simple_char_dev_test_write.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 128
#define DEV_NAME "/dev/simple_char_dev"

int main()
{
    char buffer[BUFFER_SIZE];
    int fd;

    fd = open(DEV_NAME, O_WRONLY);
    if (fd < 0)
    {
        printf("Open device %s failed\n", DEV_NAME);
        return EXIT_FAILURE;
    }

    const char *message = "Twinkle, twinkle, little bat!\n"
                          "How I wonder what you’re at!\n"
                          "Up above the world you fly,\n"
                          "Like a tea-tray in the sky.\n";
    write(fd, message, strlen(message) + 1);

    close(fd);
    return 0;
}

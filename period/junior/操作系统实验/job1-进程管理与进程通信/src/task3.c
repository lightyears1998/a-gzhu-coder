#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int fd;

void thread()
{
    #ifdef TEST_LOCK
    lockf(fd, F_LOCK, 0);
    #endif

    printf(">>>>> FILE begin <<<<<\n");
    lseek(fd, 0, SEEK_SET);
    char buf[128] = {};
    int rc = 0;
    while ((rc = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[rc] = 0;
        printf("%s", buf);
        sleep(1);
    }
    printf(">>>>> FILE end <<<<<\n");

    #ifdef TEST_LOCK
    lockf(fd, F_ULOCK, 0);
    #endif
}

int main()
{
    fd = open("./task3.c", O_RDWR);  // 若使用O_RDONLY则lockf无效。

    for (int i = 0; i < 2; ++i)
    {
        int pid = fork();
        if (pid > 0)
        {
            continue;
        }
        else
        {
            thread();
            exit(0);
        }
    }
    
    while (wait(NULL) > 0) continue;
    close(fd);
}

// task7.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pid = -1;

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("Fail to fork.");
        break;

    case 0:
        printf("This is the child process, pid = %d.\n", getpid());
        sleep(20);
        break;

    default:
        printf("This is the parent process, pid = %d.\n", getpid());
        sleep(1);
        printf("Sleep for 20 seconds...\n");
        sleep(20);

        wait(NULL);
        break;
    }
}

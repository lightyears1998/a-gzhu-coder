// task6.c

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
        exit(EXIT_FAILURE);
        break;

    default:
        printf("This is the parent process, pid = %d.\n", getpid());

        int wstatus;
        wait(&wstatus);
        printf("Child exited, status = %d.\n", WEXITSTATUS(wstatus));
        break;
    }
}

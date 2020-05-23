// demo_framework.c

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern void test(void);

int main(void)
{
    if (fork() == 0) {
        test();
    }

    int ret;
    wait(&ret);

    if (WIFEXITED(ret)) {
        printf("exited, status=%d\n", WEXITSTATUS(ret));
    }
    else if (WIFSIGNALED(ret)) {
        printf("killed by signal %d\n", WTERMSIG(ret));
    }
    else if (WIFSTOPPED(ret)) {
        printf("stopped by signal %d\n", WSTOPSIG(ret));
    }
}

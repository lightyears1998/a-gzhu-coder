// task1_fork.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pid = -1;

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("Fail to fork.\n");
        break;

    case 0:
        printf("This is child process, whose pid is %d.\n", getpid());
        execl("/bin/ps", "/bin/ps", "-o", "pid,ppid,comm", NULL);
        printf("Fail to exec!\n");
        break;

    default:
        printf("This is parent process, whose pid is %d.\n", getpid());
        wait(NULL);
        break;
    }
}

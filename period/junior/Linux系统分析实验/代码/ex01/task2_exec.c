// task2_exec.c

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
        printf("Fail to fork.");
        break;

    case 0:
        execl("/bin/ps", "/bin/ps", "-e", "-o", "comm,pid,pcpu,pmem", "--sort", "-pmem", NULL);
        break;

    default:
        wait(NULL);
        break;
    }
}

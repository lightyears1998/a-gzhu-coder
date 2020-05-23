// task1_pipes.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MESSAGE_SIZE 50

int main()
{
    int pipefd[2];
    pipe(pipefd);

    int pid1 = 0, pid2 = 0;

    pid1 = fork();
    if (pid1 == 0)
    {   // 子进程1
        sleep(3);
        lockf(pipefd[1], F_LOCK, 0);
        const char *message = "Child 1 is sending a message!";
        write(pipefd[1], message, MESSAGE_SIZE);
        sleep(3);
        lockf(pipefd[1], F_ULOCK, 0);
        exit(0);
    }
    else
    {   // 主进程
        pid2 = fork();
        if (pid2 == 0)
        {   // 子进程2
            sleep(1);
            lockf(pipefd[1], F_LOCK, 0);
            const char *message = "Child 2 is sending a message!";
            write(pipefd[1], message, MESSAGE_SIZE);
            sleep(3);
            lockf(pipefd[1], F_ULOCK, 0);
            exit(0);
        }
        else
        {   // 主进程
            char buffer[MESSAGE_SIZE];

            wait(0);
            read(pipefd[0], buffer, MESSAGE_SIZE);
            printf("%s\n", buffer);
            wait(0);
            read(pipefd[0], buffer, MESSAGE_SIZE);
            printf("%s\n", buffer);
            exit(0);
        }
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void main_process();
void child_process1();
void child_process2();
void spin();
void stop_spin();

int run_flag = 1;
int p1, p2;

int main()
{
    p1 = fork();
    if (p1) {
        p2 = fork();
        if (p2) {
            main_process();
        } else {
            child_process2();
        }
    } else {
        child_process1();
    }
}

void main_process()
{
    signal(SIGINT, stop_spin);
    spin();
    kill(p1, SIGUSR1);
    kill(p2, SIGUSR2);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    printf("Parent process is killed!\n");
    exit(0);
}

void child_process1()
{
    signal(SIGINT, SIG_IGN);  // 忽略SIGINT，避免造成干扰。
    signal(SIGUSR1, stop_spin);
    spin();
    printf("Child process1 is killed by parent!\n");
    exit(0);
}

void child_process2()
{
    signal(SIGINT, SIG_IGN);  // 忽略SIGINT，避免造成干扰。
    signal(SIGUSR2, stop_spin);
    spin();
    printf("Child process2 is killed by parent!\n");
    exit(0);
}

void spin()
{
    while (run_flag > 0) continue;
}

void stop_spin()
{
    run_flag = 0;
}

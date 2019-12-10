#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    switch(pid) {
        case -1:
            printf("Fork()失败。\n");
            exit(-1);
        case 0:
            execl("/bin/ls", "~", NULL);  // 现有进程的上下文中运行可执行文件（覆盖先前的可执行文件）。
            printf("ls()失败。\n");  // 只有在exec失败时才会输出。
            exit(-1);
        default:
            wait(NULL);  // 等待子进程完成。
            printf("子进程完成。\n");
            exit(0);
    }
}

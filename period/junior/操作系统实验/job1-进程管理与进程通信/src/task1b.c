#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

void random_sleep() {
    sleep(rand() % 3 + 1);
}

int main() {
    srand(time(NULL));

    int pid1, pid2;

    switch (pid1 = fork()) {
        case -1: break;
        case 0 /* child1 */: random_sleep(); putchar('b'); fflush(NULL); exit(0);
        default /* main */: {
            switch (pid2 = fork()) {
                case -1: break;
                case 0 /* child2 */: random_sleep(); putchar('c'); fflush(NULL); exit(0);
                default /* main */: random_sleep(); putchar('a'); fflush(NULL);
            }
        }
    }

    // main等待所有进程结束并在最后输出一个换行符。
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    putchar('\n');
}

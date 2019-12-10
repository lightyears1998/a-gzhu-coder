#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2;

    switch (pid1 = fork()) {
        case -1: /* 创建子进程失败 */
            break;
        case 0: /* child1 */ 
            putchar('b'); exit(0);
        default: {  /* main */
            switch (pid2 = fork()) {
                case -1:
                    break;
                case 0: /* child2 */
                    putchar('c'); exit(0);
                default: /* main */
                    putchar('a');
            }
        }
    }

    // main等待所有进程结束并在最后输出一个换行符。
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    putchar('\n');
}

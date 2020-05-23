// demo1.c

#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();
    while (true) {
        continue;
    }

    if (pid > 0) {
        wait(NULL);
    }
    return 0;
}

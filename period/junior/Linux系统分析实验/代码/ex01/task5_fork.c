// task5_fork.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int ref = 1;

int subprocess(void) {
    for (int i = 0; i < 3; ++i) {
        printf("Child process: ref = %d.\n", ref++);
    }
    exit(0);
}

int main(void) {
    if (fork() == 0) {
        subprocess();
    }
    for (int i = 0; i < 3; ++i) {
        printf("Parent Process: ref = %d.\n", ref++);
    }

    wait(NULL);
}

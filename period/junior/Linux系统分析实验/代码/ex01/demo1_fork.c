// demo1_fork.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int count = 0;

int subprocess(void) {
    if (count < 1000) {
        if (fork() == 0) {
            count++;
            subprocess();
            exit(0);
        }
        wait(NULL);
    }
    exit(0);
}

int main(void) {
    subprocess();
    wait(NULL);
}

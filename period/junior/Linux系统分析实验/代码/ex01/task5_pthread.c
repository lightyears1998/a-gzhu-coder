// task5_pthread.c

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ref = 1;

void subthread(void)
{
    for (int i = 0; i < 3; ++i) {
        printf("Sub thread: ref = %d.\n", ref++);
    }
}

int main(void)
{
    pthread_t id;
    pthread_create(&id, NULL, (void *)subthread, NULL);

    for (int i = 0; i < 3; ++i) {
        printf("Main thread: ref = %d.\n", ref++);
    }

    pthread_join(id, NULL);
}

// demo1_pthread.c

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;

void subthread(void)
{
    pthread_t id;
    if (count < 1000) {
        count++;
        pthread_create(&id, NULL, (void *)subthread, NULL);
        pthread_join(id, NULL);
    }
}

int main(void)
{
    subthread();
}

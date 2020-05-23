// task3_threads.c

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void thread(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        printf("This is a pthread.\n");
    }

    srand(time(NULL));
    int *retval = calloc(1, sizeof(int));
    *retval = rand() % 256;

    printf("Passing return value: %d.\n", *retval);
    pthread_exit((void *)retval);
}

int main(void)
{
    pthread_t id;

    if (pthread_create(&id, NULL, (void *)thread, NULL) != 0)
    {
        printf("Fail to create pthreads!\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        printf("This is the main thread.\n");
    }

    int *retval = NULL;
    pthread_join(id, (void **)&retval);
    printf("The return value from pthread is %d.\n", *retval);
    free(retval);
}

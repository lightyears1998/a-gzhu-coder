// task4_semaphore.c

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#define QUEUE_SIZE 3
#define NEXT_INDEX(INDEX) (((INDEX) + 1) % QUEUE_SIZE)

int queue[QUEUE_SIZE][2];
sem_t empty_count;
sem_t filled_count;
sem_t reader_mutex;
sem_t handler_mutex;
int alive_reader_count;
int reader_index;
int handler_index;

void Reader(void *dataSrc)
{
    FILE *fp = fopen((const char*)dataSrc, "r");
    while (true)
    {
        sem_wait(&empty_count);
        sem_wait(&reader_mutex);

        if (fscanf(fp, "%d %d", &queue[reader_index][0], &queue[reader_index][1]) == -1) {
            break;
        }
        reader_index = NEXT_INDEX(reader_index);

        sem_post(&filled_count);
        sem_post(&reader_mutex);
    }
    --alive_reader_count;
    sem_post(&reader_mutex);

    fclose(fp);
}

void Handler(void *operator)
{
    while (alive_reader_count > 0)
    {
        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_sec += 1;

        if (sem_timedwait(&filled_count, &timeout) == -1) {
            continue;
        }
        sem_wait(&handler_mutex);

        int a = queue[handler_index][0];
        int b = queue[handler_index][1];

        queue[handler_index][0] = 0;
        queue[handler_index][1] = 0;

        int result;
        switch (((const char*)operator)[0])
        {
        case '+': result = a + b; break;
        case '*': result = a * b; break;
        }

        printf("[%s] %2d %s %2d = %2d\n", (const char*)operator, a, (const char*)operator, b, result);
        handler_index = NEXT_INDEX(handler_index);

        sem_post(&empty_count);
        sem_post(&handler_mutex);
    }
}

int main(void)
{
    pthread_t reader1, reader2, handler1, handler2;
    sem_init(&reader_mutex, 0, 1);
    sem_init(&handler_mutex, 0, 1);
    sem_init(&empty_count, 0, QUEUE_SIZE);
    sem_init(&filled_count, 0, 0);

    pthread_create(&reader1, NULL, (void *)Reader, "task4_data1.txt");
    pthread_create(&reader2, NULL, (void *)Reader, "task4_data2.txt");
    alive_reader_count = 2;

    pthread_create(&handler1, NULL, (void *)Handler, "+");
    pthread_create(&handler2, NULL, (void *)Handler, "*");

    pthread_join(reader1, NULL);
    pthread_join(reader1, NULL);
    pthread_join(handler1, NULL);
    pthread_join(handler2, NULL);
}

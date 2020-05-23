// demo1_fixed.c

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void test(void) {
    for (long long cnt = 0; cnt < 1e7; ++cnt)
    {
        void *p = malloc(40960000);
        if (p == NULL)
        {
            printf("Can't allocate memoery!\n");
            exit(EXIT_FAILURE);
        }
        free(p);
    }
    exit(EXIT_SUCCESS);
}

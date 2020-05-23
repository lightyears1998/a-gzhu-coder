// demo6_correct.c

#include <stdlib.h>
#include <stdbool.h>

bool random(void) {
    char *tmp = malloc(8);

    if (rand() % 2 == 1) {
        free(tmp);
        return false;
    }

    free(tmp);
    return true;
}

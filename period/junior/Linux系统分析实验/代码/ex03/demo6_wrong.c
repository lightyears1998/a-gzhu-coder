// demo6_wrong.c

#include <stdbool.h>

bool random(void) {
    char *tmp = malloc(8);

    if (rand() % 2 == 1) {
        return false;
        // Forget to free(tmp) before return in this branch!
    }

    free(tmp);
    return true;
}

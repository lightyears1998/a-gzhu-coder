// demo7_wrong.c

#include <stdlib.h>

int main(void) {
    char *buffer = malloc(16);
    char *hint = malloc(16);

    // Do something...

    free(buffer);
    buffer = NULL;

    // Do something...

    free(buffer); // A NULL pointer can be safely freed.
    free(hint);
}

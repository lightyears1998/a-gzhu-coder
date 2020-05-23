// demo7_wrong.c

#include <stdlib.h>

int main(void) {
    char *buffer = malloc(16);
    char *hint = malloc(16);

    // Do something...

    free(buffer);

    // Do something...

    free(buffer); // buffer is freed twice!
    free(hint);
}

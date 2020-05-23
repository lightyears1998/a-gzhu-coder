// demo2_correct.c

#include <stdlib.h>

// Correct
void test(void) {
    void *p = malloc(4096);

    // Do something with p...

    free(p);
}

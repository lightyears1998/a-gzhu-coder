// demo2_wrong.c

#include <stdlib.h>

// Wrong
void test(void) {
    void *p = malloc(4096);

    // Do something with p...

    return; // Forget to free(p)!
}

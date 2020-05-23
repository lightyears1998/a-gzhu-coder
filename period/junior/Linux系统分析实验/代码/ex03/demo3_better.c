// demo3_better.c

#include <stdlib.h>

// Better
void iota(int *p, int len) {
    for (int i = 0; i < len; ++i) {
        p[i] = i;
    }
}

int main(void) {
    int len = 100;
    int *arr = malloc(sizeof(int) * len);
    iota(arr, len);

    // Do something with arr...

    free(arr);
}

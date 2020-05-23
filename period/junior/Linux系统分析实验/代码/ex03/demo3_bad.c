// demo3_bad.c

#include <stdlib.h>

// Bad
int* iota(int len) {
    int *p = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        p[i] = i;
    }
}

int main(void) {
    int *arr = iota(100);

    // Do somehing with arr...

    return 0; // Forget to free(arr)!
}

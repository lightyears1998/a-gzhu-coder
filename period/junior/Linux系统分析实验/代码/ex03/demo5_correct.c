// demo5_correct.c

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *tmp = malloc(16);
    strcpy(tmp, "Hello, guys!");
    printf("%s\n", tmp);

    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }

    tmp = malloc(32);
    strcpy(tmp, "I'm Tom, Nice to meet you here.");
    printf("%s\n", tmp);
}

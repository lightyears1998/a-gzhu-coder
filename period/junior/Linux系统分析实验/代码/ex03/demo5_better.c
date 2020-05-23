// demo5_better.c

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *tmp = malloc(16);
    strcpy(tmp, "Hello, guys!");
    printf("%s\n", tmp);

    tmp = realloc(tmp, 32);
    strcpy(tmp, "I'm Tom, Nice to meet you here.");
    printf("%s\n", tmp);
}

// demo5_wrong.c

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *tmp = malloc(16);
    strcpy(tmp, "Hello, guys!");
    printf("%s\n", tmp);

    tmp = malloc(32); // Forget to free(tmp) before reassigment!
    strcpy(tmp, "I'm Tom, Nice to meet you here.");
    printf("%s\n", tmp);
}

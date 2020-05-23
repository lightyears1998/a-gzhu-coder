// demo4_bad.c

#include <stdlib.h>
#include <string.h>

struct data {
    char *p;
    int size;
};

// Wrong
int main(void) {
    const char *text = "This is a text";

    struct data *pdata = malloc(sizeof(struct data));
    pdata->p = malloc(strlen(text) + 1);
    strcpy(pdata->p, text);
    pdata->size = strlen(text) + 1;

    // Do something with data...

    free(pdata);  // Forget to free(pdata -> p)!
    return 0;
}

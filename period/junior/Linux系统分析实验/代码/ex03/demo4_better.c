// demo4_better.c

#include <stdlib.h>
#include <string.h>

struct data {
    char *p;
    int size;
};

void init_data(struct data **pdata, const char *text) {
    *pdata = malloc(sizeof(struct data));

    int len = strlen(text);
    (*pdata)->p = malloc(len + 1);
    strcpy((*pdata)->p, text);
    (*pdata)->size = len;
}

void destroy_data(struct data **pdata) {
    free((*pdata)->p);
    free(*pdata);
    *pdata = NULL;
}

int main(void) {
    const char *text = "This is a text";

    struct data *pdata;
    init_data(&pdata, text);

    // Do something with pdata...

    destroy_data(&pdata);
    return 0;
}

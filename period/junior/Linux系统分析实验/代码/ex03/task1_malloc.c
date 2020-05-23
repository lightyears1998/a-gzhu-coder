// task1_malloc.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *uppercase(const char *input_string);

int main(void)
{
    char *str1 = uppercase("Hello");
    char *str2 = uppercase("Goodbye");

    printf("str1 = %s\nstr2 = %s\n", str1, str2);

    free(str1);
    free(str2);

    return 0;
}

char *uppercase(const char * input_string)
{
    char *new_string;

    if ((new_string = malloc(strlen(input_string) + 1)) == NULL)
    {
        printf("Fail to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_string, input_string);
    for (int i = 0; i < strlen(new_string); i++)
    {
        if (new_string[i] >= 97 && new_string[i] <= 122) {
            new_string[i] -= 32;
        }
    }

    return new_string;
}

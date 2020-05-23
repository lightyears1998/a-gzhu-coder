// task2_realloc.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void uppercase(const char *input_string, char **new_string);

int main(void)
{
    char *string = NULL;

    uppercase("Hello", &string);
    printf("str1 = %s\n", string);
    uppercase("Goodbye", &string);
    printf("str2 = %s\n", string);

    free(string);

    return 0;
}

void uppercase(const char *input_string, char **new_string)
{
    if (new_string == NULL)
    {
        printf("Expect a pointer to (char *) type but got a NULL pointer.\n");
        exit(EXIT_FAILURE);
    }

    if ((*new_string = realloc(*new_string, strlen(input_string) + 1)) == NULL) {
        printf("Fail to allocate memory.\n");
        exit(EXIT_FAILURE);
    };

    strcpy(*new_string, input_string);
    for (int i = 0; i < strlen(*new_string); i++)
    {
        if ((*new_string)[i] >= 97 && (*new_string)[i] <= 122)
        {
            (*new_string)[i] -= 32;
        }
    }
}

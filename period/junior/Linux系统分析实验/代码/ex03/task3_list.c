// task3_list.c

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16

typedef struct
{
    char *string;
    struct data_cell *next;
} data_cell, *data_cell_ptr;

typedef struct
{
    data_cell_ptr first_cell;
    data_cell_ptr tail_cell;
} data_head, *data_head_ptr, *data;

void data_init(data_head_ptr *ptr);
void data_append(data_head_ptr head, const char *text);
void data_display(data_head_ptr head);
void data_destroy(data_head_ptr *ptr);

int main(void)
{
    data console_data;
    data_init(&console_data);

    printf("Type some words, press Ctrl + D when done.\n");
    printf("==================\n");
    printf("(begin)\n");

    char text_buffer[BUFFER_SIZE];
    while (fgets(text_buffer, sizeof(text_buffer), stdin))
    {
        data_append(console_data, text_buffer);
    }
    printf("(Ctrl + D received, typing finished)\n");

    printf("==================\n");
    data_display(console_data);
    data_destroy(&console_data);

    return 0;
}

void data_init(data_head_ptr* ptr)
{
    *ptr = malloc(sizeof(data_head));
    (*ptr)->first_cell = NULL;
    (*ptr)->tail_cell = NULL;
}

void data_append(data_head_ptr head, const char *text)
{
    data_cell_ptr cell = (data_cell_ptr)malloc(sizeof(data_cell));
    cell->string = (char *)malloc(strlen(text) + 1);
    strcpy(cell->string, text);
    cell->next = NULL;

    if (head->tail_cell == NULL) {
        head->first_cell = head->tail_cell = cell;
    } else {
        head->tail_cell->next = (struct data_cell *)cell;
        head->tail_cell = cell;
    }
}

void data_display(data_head_ptr head)
{
    int line_count = 0, unit_count = 1;

    data_cell_ptr cur = head->first_cell;
    bool should_print_line_mark = true;
    while (cur != NULL)
    {
        const char *string = cur->string;
        size_t len = strlen(string);

        for (int i = 0; i < len; ++i) {
            if (should_print_line_mark) {
                printf("%2d > ", line_count + 1);
                should_print_line_mark = false;
            }

            fputc(string[i], stdout);

            if (string[i] == '\n') {
                ++line_count;
                should_print_line_mark = true;
            }
        }

        ++unit_count;
        cur = (data_cell_ptr)(cur->next);
    }

    printf("Input data contains %d lines of text, which cost %d storing units.\n",
        line_count, unit_count);
}

void data_destroy(data_head_ptr *ptr)
{
    data_cell_ptr cur = (*ptr)->first_cell, next;
    while (cur != NULL) {
        next = (data_cell_ptr)(cur->next);
        free(cur->string);
        free(cur);
        cur = next;
    }

    free(*ptr);
    *ptr = NULL;
}

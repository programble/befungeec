/*
 *    main.c
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

int main(int argc, char **argv)
{
    stack *s = stack_new();
    stack_push(s, (void*) 1);
    stack_push(s, (void*) 2);
    stack_push(s, (void*) 3);
    stack_item *i = s->top;
    while (i)
    {
        printf("%i, ", (int) i->value);
        i = i->next;
    }
    printf("%i\n", (int) stack_peek(s));
    printf("%i\n", (int) stack_pop(s));
    printf("%i\n", (int) stack_peek(s));
    return 0;
}

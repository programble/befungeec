/*
 *    stack.c
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#include "stack.h"

stack *stack_new()
{
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

void stack_push(stack *s, void *value)
{
    stack_item *item = malloc(sizeof(stack_item));
    if (s->top)
    {
        item->value = value;
        item->next = s->top;
        s->top = item;
    }
    else
    {
        item->value = value;
        item->next = NULL;
        s->top = item;
    }
}

void *stack_pop(stack *s)
{
    stack_item *item = s->top;
    s->top = item->next;
    void *value = item->value;
    free(item);
    return value;
}

void *stack_peek(stack *s)
{
    stack_item *item = s->top;
    return item->value;
}

int stack_length(stack *s)
{
    stack_item *item = s->top;
    int i = 0;
    while (item)
    {
        i++;
        item = item->next;
    }
    return i;
}

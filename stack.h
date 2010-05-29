/*
 *    stack.h
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

typedef struct stack_item
{
    struct stack_item *next;
    void *value;
} stack_item;

typedef struct stack
{
    stack_item *top;
} stack;

stack *stack_new();

void stack_push(stack*, void*);
void *stack_pop(stack*);
void *stack_peek(stack*);

#endif

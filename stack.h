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
    char value;
} stack_item;

typedef struct stack
{
    stack_item *top;
} stack;

stack *stack_new();

void stack_push(stack*, char);
char stack_pop(stack*);
char stack_peek(stack*);
int stack_length(stack*);
int stack_empty(stack*);

#endif

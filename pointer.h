/*
 *    pointer.h
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#ifndef __POINTER_H__
#define __POINTER_H__

#include "stack.h"

typedef struct pointer
{
    int x;
    int y;
    int dx;
    int dy;
    stack *stack;
    int strmode;
} pointer;

pointer *pointer_new();
void pointer_move(pointer*);

#endif

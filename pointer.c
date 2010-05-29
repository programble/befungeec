/*
 *    pointer.c
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#include "pointer.h"

pointer *pointer_new()
{
    pointer *p = malloc(sizeof(pointer));
    p->x = 0;
    p->y = 0;
    p->dx = 1;
    p->dy = 0;
    p->stack = stack_new();
    p->strmode = 0;
    return p;
}

void pointer_move(pointer* p)
{
    p->x += p->dx;
    p->y += p->dy;
}

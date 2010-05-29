/*
 *    board.c
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#include "board.h"

board *board_new()
{
    board *b = malloc(sizeof(board));
    b->pointer = pointer_new();
    int y, x;
    for (y = 0; y < BOARD_HEIGHT; y++)
    {
        for (x = 0; x < BOARD_WIDTH; x++)
        {
            b->data[y][x] = ' ';
        }
    }
    return b;
}

char board_get(board *b, int x, int y)
{
    return b->data[y][x];
}

void board_set(board *b, int x, int y, char value)
{
    b->data[y][x] = value;
}

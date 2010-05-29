/*
 *    board.h
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "pointer.h"

#define BOARD_WIDTH 80
#define BOARD_HEIGHT 25

typedef struct board
{
    char data[BOARD_HEIGHT][BOARD_WIDTH];
    pointer *pointer;
} board;

board *board_new();

char board_get(board*, int, int);
void board_put(board*, int, int, char);

#endif

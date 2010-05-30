/*
 *    main.c
 *
 *    Copyright 2010 Curtis (Programble) <programble@gmail.com>
 *    Licensed under the GNU GPLv3
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "board.h"

void process(board *board)
{
    while (1)
    {
        char c = board_get(board, board->pointer->x, board->pointer->y);
        if (board->pointer->strmode && c != '"')
        {
            stack_push(board->pointer->stack, c);
        }
        else
        {
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            stack_push(board->pointer->stack, (char) atoi(&c));
            break;
        case '+':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, a + b);
            break;
        }
        case '-':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, b - a);
            break;
        }
        case '*':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, a * b);
            break;
        }
        case '/':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, b / a);
            break;
        }
        case '%':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, b % a);
            break;
        }
        case '!':
            stack_push(board->pointer->stack, !stack_pop(board->pointer->stack));
            break;
        case '`':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, (b > a));
            break;
        }
        case '>':
            board->pointer->dx = 1;
            board->pointer->dy = 0;
            break;
        case '<':
            board->pointer->dx = -1;
            board->pointer->dy = 0;
            break;
        case '^':
            board->pointer->dx = 0;
            board->pointer->dy = -1;
            break;
        case 'v':
            board->pointer->dx = 0;
            board->pointer->dy = 1;
            break;
        case '?':
        {
            srand((unsigned)time(NULL));
            int r = rand() % 4;
            switch (r)
            {
            case 0:
                board->pointer->dx = 1;
                board->pointer->dy = 0;
                break;
            case 1:
                board->pointer->dx = -1;
                board->pointer->dy = 0;
                break;
            case 2:
                board->pointer->dx = 0;
                board->pointer->dy = -1;
                break;
            case 3:
                board->pointer->dx = 0;
                board->pointer->dy = 1;
                break;
            }
        }
        case '_':
        {
            char x = stack_pop(board->pointer->stack);
            if (x == 0)
            {
                board->pointer->dx = 1;
                board->pointer->dy = 0;
            }
            else
            {
                board->pointer->dx = -1;
                board->pointer->dy = 0;
            }
            break;
        }
        case '|':
        {
            char x = stack_pop(board->pointer->stack);
            if (x == 0)
            {
                board->pointer->dx = 0;
                board->pointer->dy = 1;
            }
            else
            {
                board->pointer->dx = 0;
                board->pointer->dy = -1;
            }
            break;
        }
        case '"':
            board->pointer->strmode = !board->pointer->strmode;
            break;
        case ':':
            stack_push(board->pointer->stack, stack_peek(board->pointer->stack));
            break;
        case '\\':
        {
            char a = stack_pop(board->pointer->stack);
            char b = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, a);
            stack_push(board->pointer->stack, b);
            break;
        }
        case '$':
            stack_pop(board->pointer->stack);
            break;
        case '.':
            printf("%i ", stack_pop(board->pointer->stack));
            break;
        case ',':
            printf("%c", stack_pop(board->pointer->stack));
            break;
        case '#':
            pointer_move(board->pointer);
            break;
        case 'p':
        {
            int y = stack_pop(board->pointer->stack);
            int x = stack_pop(board->pointer->stack);
            char v = stack_pop(board->pointer->stack);
            board_put(board, x, y, v);
            break;
        }
        case 'g':
        {
            int y = stack_pop(board->pointer->stack);
            int x = stack_pop(board->pointer->stack);
            stack_push(board->pointer->stack, board_get(board, x, y));
            break;
        }
        case '&':
        {
            int i;
            scanf("%d", &i);
            stack_push(board->pointer->stack, (char) i);
            break;
        }
        case '~':
            stack_push(board->pointer->stack, getchar());
            break;
        case '@':
            return;
        }
        }
        pointer_move(board->pointer);
    }
}


int main(int argc, char **argv)
{
#ifdef DEBUG
    board *board = board_new();
    char data[] = "025*\"!dlroW ,olleH\">:#,_@";
    int i;
    for (i = 0; i < 25; i++)
    {
        board_put(board, i, 0, data[i]);
    }
    process(board);
#endif
    return 0;
}

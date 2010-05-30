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
            break;
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
        if (board->pointer->x < 0)
        {
            board->pointer->x += BOARD_WIDTH;
        }
        if (board->pointer->x >= BOARD_WIDTH)
        {
            board->pointer->x -= BOARD_WIDTH;
        }
        if (board->pointer->y < 0)
        {
            board->pointer->y += BOARD_HEIGHT;
        }
        if (board->pointer->y >= BOARD_HEIGHT)
        {
            board->pointer->y -= BOARD_HEIGHT;
        }
    }
}


int main(int argc, char **argv)
{
    board *board = board_new();
    FILE *f;
    if (argc < 2)
    {
        f = stdin;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f == NULL)
        {
            perror("open");
            return 1;
        }
    }
    char c;
    int x = 0;
    int y = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        else
        {
            board_put(board, x, y, c);
        }
        x++;
        if (x > BOARD_WIDTH || y > BOARD_HEIGHT)
        {
            fprintf(stderr, "Error: File too large (%i, %i)", x, y);
            return 1;
        }
    }
    if (f != stdin)
    {
        fclose(f);
    }
    process(board);
    return 0;
}

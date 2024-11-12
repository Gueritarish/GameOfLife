#include "game.h"

#include <stdio.h>
#include <stdlib.h>

int** create_board(size_t x, size_t y)
{
    int** board = calloc(y, sizeof(int *));
    if (!board)
        return NULL;
    int n = -1;
    for (size_t i = 0; i < y; i++)
    {
        board[i] = calloc(x, sizeof(int));
        if (!board[i])
            n = i;
    }
    if (n != -1)
    {
        for (int i = 0; i < n; i++)
            free(board[i]);
        free(board);
        return NULL;
    }
    return board;
}

void free_game_board(game* game)
{
    if (!game->board)
        return;
    for (size_t i = 0; i < game->y; i++)
    {
        free(game->board[i]);
    }
    free(game->board);
}

uint check_neighbours(game* game, size_t y, size_t x)
{
    uint score = 0;
    size_t min_y = (y == 0) ? 0 : y - 1;
    size_t max_y = (y == game->y - 1) ? y : y + 1;
    size_t min_x = (x == 0) ? 0 : x - 1;
    size_t max_x = (x == game->x - 1) ? x : x + 1;
    for (size_t i = min_y; i <= max_y; i++)
    {
        for (size_t j = min_x; j <= max_x; j++)
        {
            if (game->board[i][j] == ALIVE)
                score++;
        }
    }
    return score - game->board[y][x];
}

void process_next_iteration(game* game)
{
    int copy_board[game->y][game->x];
    for (size_t i = 0; i < game->y; i++)
    {
        for (size_t j = 0; j < game->x; j++)
        {
            uint score = check_neighbours(game, i,j);
            if (game->board[i][j] == ALIVE)
            {
                if (score < game->underpop || score > game->overpop)
                    copy_board[i][j] = DEAD;
                else
                    copy_board[i][j] = ALIVE;
            }
            else
            {
                if (score > game->underpop && score <= game->overpop)
                    copy_board[i][j] = ALIVE;
                else
                    copy_board[i][j] = DEAD;
            }
        }
    }
    for (size_t i = 0; i < game->y; i++)
    {
        for (size_t j = 0; j < game->x; j++)
            game->board[i][j] = copy_board[i][j];
    }
}

void display(game* game)
{
    printf("\033[1;1H");
    for (size_t i = 0; i < 2 * game->x + 2; i++)
        printf("%s ",RED);
    printf("%s\n",RESET);
    for (size_t i = 0; i < game->y; i++)
    {
        printf("%s ", RED);
        for (size_t j = 0; j < game->x; j++)
        {
            printf("%s %s ", (game->board[i][j] == ALIVE) ? WHITE : RESET, RESET);
        }
        printf("%s %s\n", RED,RESET);
    }
    for (size_t i = 0; i < 2 * game->x + 2; i++)
        printf("%s ",RED);
    printf("%s\n",RESET);
}   
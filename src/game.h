#pragma once

#include <stddef.h>

#define ALIVE 1
#define DEAD 0

#define RED "\033[48;2;255;0;0m"
#define WHITE "\033[48;2;255;255;255m"
#define RESET "\033[0m"

typedef unsigned int uint;

typedef struct game
{
    size_t x,y;
    uint underpop, overpop;
    int** board;
} game;


int** create_board(size_t x, size_t y);
void free_game_board(game* game);

void process_next_iteration(game* game);

void display(game* game);
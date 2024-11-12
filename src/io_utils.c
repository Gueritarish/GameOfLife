#include "io_utils.h"

#include <stdio.h>

void load_game(game* game, char* file_path)
{
    FILE* file = fopen(file_path, "r");
    if (!file)
    {
        printf("No file provided using '%s' as path\n", file_path);
        return;
    }

    // Get the width
    size_t width = 0;
    int c = fgetc(file);
    while (c != ' ')
    {
        width = width * 10 + c - '0';
        c = fgetc(file);
    }

    c = fgetc(file); // '\n'
    // Get the height
    size_t height = 0;
    while(c != '\n')
    {
        height = height * 10 + c -'0';
        c = fgetc(file);
    }
    if (width != game->x || height != game->y)
    {
        printf("%s format won't match given arguments, please verify that the arguments and the file match.\n", file_path);
        return;
    }

    game->board = create_board(width, height);

    for (size_t i = 0; i < game->y; i++)
    {
        for (size_t j = 0; j < game->x; j++)
        {
            c = fgetc(file);
            if (c != '0' && c != '1')
            {
                free_game_board(game);
                printf("Data in %s file isn't valid.\n", file_path);
                return;
            }
            game->board[i][j] = c - '0';
        }
        fgetc(file); // Remove \n
    }
}

void save_game(game* game, char* file_path)
{
    FILE* file = fopen(file_path,"w");
    fprintf(file,"%ld %ld\n",game->y,game->x);
    for (size_t i = 0; i < game->y; i++)
    {
        for (size_t j = 0; j < game->x; j++)
            fputc(game->board[i][j] + '0', file);
        fputc('\n', file);
    }
}
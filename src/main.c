#include "game.h"
#include "io_utils.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    game game;
    
    game.x = 100;
    game.y = 100;
    game.overpop = 3;
    game.underpop = 2;

    int iteration = 100000;
    int save = 0;
    int load = 1;
    

    if (load)
        load_game(&game, "game_temp.data");
    else
    {
        int** board = create_board(game.x,game.y);
        game.board = board;
    }

    if (!game.board)
        return 1;

    if (save)
        save_game(&game, "game_temp.data");
    printf("\033[2J");
    printf("\033[?25l");
    for (int i = 0; i < iteration; i++)
    {
        display(&game);
        process_next_iteration(&game);
        usleep(50000);
    }
    display(&game);

    free_game_board(&game);
    printf("\033[?25h");
    return 0;
}
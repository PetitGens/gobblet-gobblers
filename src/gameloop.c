#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/board.h"
#include "../headers/gameloop.h"
#include "../headers/display.h"
#include "../headers/turn.h"
#include "../headers/input.h"
#include "../headers/rating.h"

void pvp_loop(board game)
{
    clear_screen();
    
    char player1_name[NAME_MAX_LENGTH];
    char player2_name[NAME_MAX_LENGTH];
    
    input_players_names(player1_name, player2_name);
    delete_carriage_return(player1_name);
    delete_carriage_return(player2_name);

    rating ratings[2];
    strcpy(ratings[0].player_name, player1_name);
    strcpy(ratings[1].player_name, player2_name);
    
    int play_again = 1;

    while(play_again)
    {
        if (human_turn(game, player1_name, player2_name) == 1)
            play_again = 0;
        else
            play_again = declare_winner_rating(&game, ratings);
    }
    
    destroy_game(game);
}

void pvp_start()
{
    board game = new_game();
    pvp_loop(game);
}

void pvp_load()
{
    char filename[FILENAME_MAX_LENGTH];

    printf("Please enter the save file name >");
    
    input_filename(filename);

    board game = load_game(filename);
    if (game == NULL)
    {
        error_message("The file cannot be opened, or its format is incorrect.");
    }
    else
    {
        pvp_loop(game);
    }
}

void pvb_loop(board game, bot_difficulty_e bot_dif)
{
    clear_screen();
    
    char player1_name[NAME_MAX_LENGTH];
    char player2_name[NAME_MAX_LENGTH];
    
    input_single_player_name(player1_name);
    delete_carriage_return(player1_name);

    strcpy(player2_name, "Bot");

    /*rating ratings[2];
    strcpy(ratings[0].player_name, player1_name);
    strcpy(ratings[1].player_name, player2_name);*/
    
    int play_again = 1;

    while(play_again)
    {
        if (next_player(game) == PLAYER_1){
            if (human_turn(game, player1_name, player2_name) == 1)
                play_again = 0;
        }
        else{
            bot_turn(game, player1_name, player2_name, bot_dif);
        }

        if (play_again == 1){
            play_again = declare_winner_no_rating(&game, player1_name, player2_name);
        }
    }
    
    destroy_game(game);
}

void pvb_start(bot_difficulty_e bot_dif)
{
    board game = new_game();
    pvb_loop(game, bot_dif);
}

void pvb_load(bot_difficulty_e bot_dif)
{
    char filename[FILENAME_MAX_LENGTH];

    printf("Please enter the save file name >");
    
    input_filename(filename);

    board game = load_game(filename);
    if (game == NULL)
    {
        error_message("The file cannot be opened, or its format is incorrect.");
    }
    else
    {
        pvb_loop(game, bot_dif);
    }
}
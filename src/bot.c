#include <stdio.h>
#include <stdlib.h>

#include "../headers/bot.h"
#include "../headers/turn.h"
#include "../headers/display.h"
#include "../headers/input.h"

void bot_play(board game, player bot_player_num, bot_difficulty_e bot_dif, char bot_name[], char turn_message[])
{
    enum action_e action;
    int input1[2];
    int input2[2];

    switch (bot_dif)
    {
        case EASY:
            bot_easy(game, bot_player_num, &action, input1, input2);
            break;
        default :
            printf("error, invalid bot difficulty\n");
    }

    if (action == PLACE)
    {
        if (place_piece(game, input1[0], input2[0], input2[1]) != OK)
            printf("error, placement failure\n");
    }
    else if (action == MOVE)
    {
        if (move_piece(game, input1[0], input1[1], input2[0], input2[1]))
            printf("error, movement failure\n");
    }
    else
    {
        printf("error, invalid bot action, action = %d\n", action);
        turn_message[0] = '\0';
        return;
    }
    
    bot_turn_message(turn_message, bot_name, action, input1, input2);
}

void bot_easy(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    random_action(game, bot_player_num, p_action, input1, input2);
}

void random_action(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    enum possible_e possible_action = determine_possible_action(game, bot_player_num);

    if (possible_action == PLACE_ONLY)
    {
        *p_action = PLACE;
    }
    else if (possible_action == MOVE_ONLY)
    {
        *p_action = MOVE;
    }
    else
    {
        *p_action = rand() % 2 + 1;
    }
    
    if (*p_action == PLACE)
    {
        random_place(game, &input1[0], input2);
    }
    else
    {
        random_move(game, input1, input2);
    }
}

void random_place(board game, int* p_size, int dest[2])
{
    do {
        *p_size = rand() % NB_SIZE + 1;
        dest[0] = rand() % DIMENSIONS;
        dest[1] = rand() % DIMENSIONS;
    } while (is_placement_possible(game, *p_size, dest[0], dest[1]) != OK);
}

void random_move(board game, int src[2], int dest[2])
{
    do {
        src[0] = rand() % DIMENSIONS;
        src[1] = rand() % DIMENSIONS;
        dest[0] = rand() % DIMENSIONS;
        dest[1] = rand() % DIMENSIONS;
    } while (is_movement_possible(game, src[0], src[1], dest[0], dest[1]) != OK);
}
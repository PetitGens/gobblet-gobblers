#include <stdio.h>
#include <stdlib.h>

#include "../headers/bot.h"
#include "../headers/turn.h"
#include "../headers/display.h"
#include "../headers/input.h"

#define RECURSIVE_LIMIT 3
#define RANDOM_GAMES_NUMBER 50

#ifdef DEBUG
int allocated_board = 0;
#endif

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
        case MEDIUM_DIFF:
            bot_medium(game, bot_player_num, &action, input1, input2);
            break;
        case HARD:
            bot_hard(game, bot_player_num, &action, input1, input2);
            break;
        default :
            printf("difficulty = %d\n", bot_dif);
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
    if (try_to_win(game, bot_player_num, p_action, input1, input2) == 0)
        random_action(game, bot_player_num, p_action, input1, input2);
}

void bot_medium(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    if (try_to_win(game, bot_player_num, p_action, input1, input2) == 1)
    {
		#ifdef DEBUG
        printf("je peux gagner\n");
        #endif
        return;
    }

    if (try_to_block_oppo(game, bot_player_num) == 0)
    {
        random_action(game, bot_player_num, p_action, input1, input2);
        #ifdef DEBUG
        printf("je ne peux pas bloquer\n");
        #endif
        return;
    }
    #ifdef DEBUG
    printf("je peux jouer pour empécher la victoire de l'adversaire\n");
    #endif

    enum return_code ret = OK;
    int oppo_can_win = 1;

    while(ret != OK || oppo_can_win == 1)
    {
        random_action(game, bot_player_num, p_action, input1, input2);

        #ifdef DEBUG
        allocated_board++;
        #endif
        board copy = copy_game(game);
        
        
        if (*p_action == PLACE)
        {
            ret = place_piece(copy, input1[0], input2[0], input2[1]);
        }
        else
        {
            ret = move_piece(copy, input1[0], input1[1], input2[0], input2[1]);
        }

        enum action_e action;
        int tab1[2], tab2[2];
        oppo_can_win = try_to_win(copy, bot_player_num % 2 + 1, &action, tab1, tab2);
        #ifdef DEBUG
        allocated_board--;
        #endif
        destroy_game(copy);
    }
}

void bot_hard(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    movement_s the_move;
    int value = minimax(game, bot_player_num, 0, &the_move, 0, 0, 0);
    #ifdef DEBUG
    printf("%d\n", value);
    #endif
    
    if (value == 0)
    {
		bot_medium(game, bot_player_num, p_action, input1, input2);
		return;
	}
    else if (value == RANDOM_GAMES_NUMBER)
    {
        if (try_to_win(game, bot_player_num, p_action, input1, input2) == 1)
        {
            return;
        }
    }
    
    *p_action = the_move.action;
    input1[0] = the_move.input1[0];
    input1[1] = the_move.input1[1];
    input2[0] = the_move.input2[0];
    input2[1] = the_move.input2[1];
}

void random_action(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    /*enum possible_e possible_action = determine_possible_action(game, bot_player_num);

    if (possible_action == PLACE_ONLY)
    {
        *p_action = PLACE;
    }
    else if (possible_action == MOVE_ONLY)
    {
        *p_action = MOVE;
    }*/

    int is_action_possible = 0;

    while(is_action_possible == 0)
    {
        *p_action = rand() % 2 + 1;

        
        if (*p_action == PLACE)
        {
            random_place(game, &input1[0], input2);
            if (is_placement_possible(game, input1[0], input2[0], input2[1]) == OK)
            {
                is_action_possible = 1;
            }
        }
        else
        {
            random_move(game, input1, input2);
            if (is_movement_possible(game, input1[0], input1[1], input2[0], input2[1]) == OK)
            {
                is_action_possible = 1;
            }
        }
    } 
}

void random_place(board game, int* p_size, int dest[2])
{
    *p_size = rand() % NB_SIZE + 1;
    dest[0] = rand() % DIMENSIONS;
    dest[1] = rand() % DIMENSIONS;
}

void random_move(board game, int src[2], int dest[2])
{
    src[0] = rand() % DIMENSIONS;
    src[1] = rand() % DIMENSIONS;
    dest[0] = rand() % DIMENSIONS;
    dest[1] = rand() % DIMENSIONS;
}

int try_to_win(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    enum possible_e possible = determine_possible_action(game, bot_player_num);

    for (enum action_e action = 1; action <= 2; action++)
    {
        if (action == PLACE && possible != MOVE_ONLY)
        {
            for (size s = SMALL; s <= LARGE; s++)
            {
                for (int line = 0; line < 3; line++)
                {
                    for (int col = 0; col < 3; col++)
                    {
                        #ifdef DEBUG
                        allocated_board++;
                        #endif
                        board copy = copy_game(game);
                        place_piece(copy, s, line, col);
                        if (get_winner(copy) == bot_player_num)
                        {
                            *p_action = action;
                            input1[0] = s;
                            input2[0] = line;
                            input2[1] = col;
                            #ifdef DEBUG
                            allocated_board--;
                            #endif
                            destroy_game(copy);

                            return 1;
                        }
                        #ifdef DEBUG
                        allocated_board--;
                        #endif
                        destroy_game(copy);
                    }
                }
            }
        }
        else if (action == MOVE && possible != PLACE_ONLY)
        {
            for (int src_line = 0; src_line < 3; src_line++)
            {
                for (int src_col = 0; src_col < 3; src_col++)
                {
                    for (int dest_line = 0; dest_line < 3; dest_line++)
                    {
                        for (int dest_col = 3; dest_col < 3; dest_col++)
                        {
                            #ifdef DEBUG
                            allocated_board++;
                            #endif
                            board copy = copy_game(game);
                            move_piece(copy, src_line, src_col, dest_line, dest_col);
                            if (get_winner(copy) == bot_player_num)
                            {
                                *p_action = action;
                                input1[0] = src_line;
                                input2[1] = src_col;
                                input2[0] = dest_line;
                                input2[1] = dest_col;
                                #ifdef DEBUG
                                allocated_board--;
                                #endif
                                destroy_game(copy);

                                return 1;
                            }
                            #ifdef DEBUG
                            allocated_board--;
                            #endif
                            destroy_game(copy);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int try_to_block_oppo(board game, player bot_player_num)
{
    enum possible_e possible = determine_possible_action(game, bot_player_num);

    for (enum action_e action = 1; action <= 2; action++)
    {
        if (action == PLACE && possible != MOVE_ONLY)
        {
            for (size s = SMALL; s <= LARGE; s++)
            {
                for (int line = 0; line < 3; line++)
                {
                    for (int col = 0; col < 3; col++)
                    {
                        #ifdef DEBUG
                        allocated_board++;
                        #endif
                        board copy = copy_game(game);
                        if (place_piece(copy, s, line, col) == OK){
                            enum action_e action;
                            int input1[2], input2[2];

                            if (try_to_win(copy, bot_player_num % 2 + 1, &action, input1, input2) == 0)
                            {
                                #ifdef DEBUG
                                allocated_board--;
                                #endif
                                destroy_game(copy);
                                return 1;
                            }
                        }
                        #ifdef DEBUG
                        allocated_board--;
                        #endif
                        destroy_game(copy);
                    }
                }
            }
        }
        else if (action == MOVE && possible != PLACE_ONLY)
        {
            for (int src_line = 0; src_line < 3; src_line++)
            {
                for (int src_col = 0; src_col < 3; src_col++)
                {
                    for (int dest_line = 0; dest_line < 3; dest_line++)
                    {
                        for (int dest_col = 3; dest_col < 3; dest_col++)
                        {
                            #ifdef DEBUG
                            allocated_board++;
                            #endif
                            board copy = copy_game(game);
                            if (move_piece(copy, src_line, src_col, dest_line, dest_col) == OK) {
                                enum action_e action;
                                int input1[2], input2[2];

                                if (try_to_win(copy, bot_player_num % 2 + 1, &action, input1, input2) == 0)
                                {
                                    #ifdef DEBUG
                                    allocated_board--;
                                    #endif
                                    destroy_game(copy);
                                    return 1;
                                }
                            }
                            #ifdef DEBUG
                            allocated_board--;
                            #endif
                            destroy_game(copy);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int minimax(board game, player bot_player_num, int depth, movement_s* p_movement, int uncle, int great_uncle, int great_great_uncle)
{
    if (depth > RECURSIVE_LIMIT)
    {
        return random_games(game, bot_player_num);
    }

    if (next_player(game) == bot_player_num)
    {
        enum possible_e possible = determine_possible_action(game, bot_player_num);

        int max = -100;

        for (enum action_e action = PLACE; action <= MOVE; action++)
        {
            if (action == PLACE && possible != MOVE_ONLY)
            {
                for (size s = SMALL; s <= LARGE; s++)
                {
                    for (int line = 0; line < 3; line++)
                    {
                        for (int col = 0; col < 3; col++)
                        {
                            #ifdef DEBUG
                            allocated_board++;
                            #endif
                            board copy = copy_game(game);
                            if (place_piece(copy, s, line, col) == OK)
                            {
                                int value;

                                if (get_winner(copy) == bot_player_num)
                                {
                                    value = RANDOM_GAMES_NUMBER;
                                }
                                else if (get_winner(copy) == bot_player_num % 2 + 1)
                                {
                                    value = 0;
                                }
                                else
                                {
                                    
                                    #ifdef DEBUG
                                    //print_board(copy);
                                    //printf("recursive minimax call ; depth=%d, action=place, size=%d, line=%d; col=%d\n", depth, s, line, col);
                                    //printf("allocated=%d\n", allocated_board);
                                    #endif
                                    value = minimax(copy, bot_player_num, depth + 1, p_movement, max, uncle, great_uncle);
                                    #ifdef DEBUG
                                    //printf("value=%d\n", value);
                                    //printf("out of minimax\n");
                                    #endif
                                }

                                if (depth > 0 && value > uncle)
                                {
                                    #ifdef DEBUG
                                    allocated_board--;
                                    #endif
                                    destroy_game(copy);
                                    return RANDOM_GAMES_NUMBER + 1;
                                }
                                if (depth > 3 && value > great_great_uncle)
                                {
                                    #ifdef DEBUG
                                    allocated_board--;
                                    #endif
                                    destroy_game(copy);
                                    return RANDOM_GAMES_NUMBER + 2;
                                }

                                if (value > max)
                                {
                                    max = value;
                                    if (depth == 0)
                                    {
                                        p_movement->action = action;
                                        p_movement->input1[0] = s;
                                        p_movement->input2[0] = line;
                                        p_movement->input2[1] = col;
                                    }
                                }
                            }
                            #ifdef DEBUG
                            allocated_board--;
                            #endif
                            destroy_game(copy);
                        }
                    }
                }
            }
            else if (action == MOVE && possible != PLACE_ONLY)
            {
                for (int src_line = 0; src_line < 3; src_line++)
                {
                    for (int src_col = 0; src_col < 3; src_col++)
                    {
                        for (int dest_line = 0; dest_line < 3; dest_line++)
                        {
                            for (int dest_col = 0; dest_col < 3; dest_col++)
                            {
                                #ifdef DEBUG
                                allocated_board++;
                                #endif
                                board copy = copy_game(game);
                                
                                if (move_piece(copy, src_line, src_col, dest_line, dest_col) == OK)
                                {
                                    int value;

                                    if (get_winner(copy) == bot_player_num)
                                    {
                                        value = RANDOM_GAMES_NUMBER;
                                    }
                                    else if (get_winner(copy) == bot_player_num % 2 + 1)
                                    {
                                        value = 0;
                                    }
                                    else
                                    {
                                        #ifdef DEBUG
                                        //print_board(copy);
                                        //printf("recursive minimax call ; depth=%d, action=move, src_line=%d, src_col=%d, dest_line=%d; dest_col=%d\n",
                                        //    depth, src_line, src_col, dest_line, dest_col);
                                        //printf("allocated=%d\n", allocated_board);
                                        #endif
                                        value = minimax(copy, bot_player_num, depth + 1, p_movement, max, uncle, great_uncle);
                                        #ifdef DEBUG
                                        //printf("value=%d\n", value);
                                        //printf("out of minimax\n");
                                        #endif
                                    }

                                    if (depth > 0 && value > uncle)
                                    {
                                        #ifdef DEBUG
                                        allocated_board--;
                                        #endif
                                        destroy_game(copy);
                                        return RANDOM_GAMES_NUMBER + 1;
                                    }
                                    if (depth > 3 && value > great_great_uncle)
                                    {
                                        #ifdef DEBUG
                                        allocated_board--;
                                        #endif
                                        destroy_game(copy);
                                        return RANDOM_GAMES_NUMBER + 2;
                                    }

                                    if (value > max)
                                    {
                                        max = value;
                                        if (depth == 0)
                                        {
                                            p_movement->action = action;
                                            p_movement->input1[0] = src_line;
                                            p_movement->input1[1] = src_col;
                                            p_movement->input2[0] = dest_line;
                                            p_movement->input2[1] = dest_col;
                                        }
                                    }
                                }
                                #ifdef DEBUG
                                allocated_board--;
                                #endif
                                destroy_game(copy);
                            }
                        }
                    }
                }
            }
        }
        return max;
    }

    // next_player(game) != bot_player num

    enum possible_e possible = determine_possible_action(game, bot_player_num % 2 + 1);
    
    #ifdef DEBUG
    //printf("possible=%d, depth=%d\n", possible, depth);
    #endif

    int min = 3 * RANDOM_GAMES_NUMBER;

    for (enum action_e action = 1; action <= 2; action++)
    {
        if (action == PLACE && possible != MOVE_ONLY)
        {
            for (size s = SMALL; s <= LARGE; s++)
            {
                for (int line = 0; line < 3; line++)
                {
                    for (int col = 0; col < 3; col++)
                    {
                        #ifdef DEBUG
                        allocated_board++;
                        #endif
                        board copy = copy_game(game);
                        if (place_piece(copy, s, line, col) == OK)
                        {
                            int value;

                            if (get_winner(copy) == bot_player_num)
                            {
                                value = RANDOM_GAMES_NUMBER;
                            }
                            else if (get_winner(copy) == bot_player_num % 2 + 1)
                            {
                                value = 0;
                            }
                            else
                            {
                                #ifdef DEBUG
                                //print_board(copy);
                                //printf("recursive minimax call ; depth=%d, action=place, size=%d, line=%d; col=%d\n", depth, s, line, col);
                                //printf("allocated=%d\n", allocated_board);
                                #endif
                                value = minimax(copy, bot_player_num, depth + 1, p_movement, min, uncle, great_uncle);
                                #ifdef DEBUG
                                //printf("value=%d\n", value);
                                //printf("out of minimax\n");
                                #endif
                            }

                            if (depth > 0 && value < uncle)
                            {
                                #ifdef DEBUG
                                allocated_board--;
                                #endif
                                destroy_game(copy);
                                return -1;
                            }
                            if (depth > 3 && value < great_great_uncle)
                            {
                                #ifdef DEBUG
                                allocated_board--;
                                #endif
                                destroy_game(copy);
                                return -2;
                            }

                            if (value < min)
                            {
                                min = value;
                                if (depth == 0)
                                {
                                    p_movement->action = action;
                                    p_movement->input1[0] = s;
                                    p_movement->input2[0] = line;
                                    p_movement->input2[1] = col;
                                }
                            }
                        }
                        #ifdef DEBUG
                        allocated_board--;
                        #endif
                        destroy_game(copy);
                    }
                }
            }
        }
        else if (action == MOVE && possible != PLACE_ONLY)
        {
            for (int src_line = 0; src_line < 3; src_line++)
            {
                for (int src_col = 0; src_col < 3; src_col++)
                {
                    for (int dest_line = 0; dest_line < 3; dest_line++)
                    {
                        for (int dest_col = 0; dest_col < 3; dest_col++)
                        {
                            if (depth == 1)
                            {
                                ;
                            }
                            #ifdef DEBUG
                            allocated_board++;
                            #endif
                            board copy = copy_game(game);
                            
                            if (move_piece(copy, src_line, src_col, dest_line, dest_col) == OK)
                            {
                                int value;

                                if (get_winner(copy) == bot_player_num)
                                {
                                    value = RANDOM_GAMES_NUMBER;
                                }
                                else if (get_winner(copy) == bot_player_num % 2 + 1)
                                {
                                    value = 0;
                                }
                                else
                                {
                                    #ifdef DEBUG
                                    //print_board(copy);
                                    //printf("recursive minimax call ; depth=%d, action=move, src_line=%d, src_col=%d, dest_line=%d; dest_col=%d\n",
                                    //    depth, src_line, src_col, dest_line, dest_col);
                                    //printf("allocated=%d\n", allocated_board);
                                    #endif
                                    value = minimax(copy, bot_player_num, depth + 1, p_movement, min, uncle, great_uncle);
                                    #ifdef DEBUG
                                    //printf("value=%d\n", value);
                                    //printf("out of minimax\n");
                                    #endif
                                }

                                if (depth > 0 && value < uncle)
                                {
                                    #ifdef DEBUG
                                    allocated_board--;
                                    #endif
                                    destroy_game(copy);
                                    return -1;
                                }
                                if (depth > 3 && value < great_great_uncle)
                                {
                                    #ifdef DEBUG
                                    allocated_board--;
                                    #endif
                                    destroy_game(copy);
                                    return -2;
                                }

                                if (value < min)
                                {
                                    min = value;
                                    if (depth == 0)
                                    {
                                        p_movement->action = action;
                                        p_movement->input1[0] = src_line;
                                        p_movement->input1[1] = src_col;
                                        p_movement->input2[0] = dest_line;
                                        p_movement->input2[1] = dest_col;
                                    }
                                }
                            }
                            #ifdef DEBUG
                            allocated_board--;
                            #endif
                            destroy_game(copy);
                        }
                    }
                }
            }
        }
    }
    return min;
}

int random_games(board game, player bot_player_num)
{
    int win_count = 0;

    for (int i = 0; i < RANDOM_GAMES_NUMBER; i++)
    {
        #ifdef DEBUG
        allocated_board++;
        #endif
        board copy = copy_game(game);

        player winner = get_winner(copy);

        while(winner == NO_PLAYER)
        {

            movement_s move_s;
            random_action(copy, next_player(copy),&(move_s.action), move_s.input1, move_s.input2);

            if (move_s.action == PLACE)
            {
                place_piece(copy, move_s.input1[0], move_s.input2[0], move_s.input2[1]);
                //printf("place_piece(game, %d, %d, %d);\n", move_s.input1[0], move_s.input2[0], move_s.input2[1]);
            }
            else
            {
                move_piece(copy, move_s.input1[0], move_s.input1[1], move_s.input2[0], move_s.input2[1]);
                //printf("move_piece(game, %d, %d, %d, %d);\n", move_s.input1[0], move_s.input1[1], move_s.input2[0], move_s.input2[1]);
            }

            #ifdef DEBUG
            /*char message[64];
            char player_name[16];
            sprintf(player_name, "Player%d", next_player(copy) % 2 + 1);
            bot_turn_message(message, player_name, move_s.action, move_s.input1, move_s.input2);
            printf("%s\n", message);*/
            //print_board(copy);
            #endif
           

            

            winner = get_winner(copy);
        }

        if (winner == bot_player_num)
        {
            win_count++;
        }
        #ifdef DEBUG
        allocated_board--;
        //printf("allocated=%d\n", allocated_board);
        #endif
        destroy_game(copy);
        
        #ifdef DEBUG
        //printf("win_count=%d\n", win_count);
        #endif

        //printf("\n\n\n\n");
    }

    return win_count;
}

/*int try_to_win(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
{
    int places[8][3];
    int nb_places = winnable_places(game, bot_player_num, places);
    int found = 0, i = 0;
    
    while(found == 0 && i < nb_places)
    {
        int column = places[i][0], line = places[i][1];
        direction_e dir = places[i][2];

        switch(dir)
        {
            case HORIZONTAL:
                found = try_to_win_horizontal(game, bot_player_num, p_action, input1, input2, line, column);
                break;
            case VERTICAL:
                found = try_to_win_vertical(game, bot_player_num, p_action, input1, input2, line, column);
                break;
            case DIAGONAL_DOWN:
                found = try_to_win_diagonal_down(game, bot_player_num, p_action, input1, input2, line, column);
                break;
            case DIAGONAL_UP:
                found = try_to_win_diagonal_up(game, bot_player_num, p_action, input1, input2, line, column);
                break;
        }
        i++;
    }

    return 0;
}

int try_to_win_horizontal(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2], int line, int column)
{
    size not_owned_size = get_piece_size(game, line, column);

    for (size s = not_owned_size + 1; s <= LARGE; s++)
    {
        if (get_nb_piece_in_house(game, bot_player_num, s) > 0)
        {
            *p_action = PLACE;
            input1[0] = s;
            input2[0] = line;
            input2[1] = column;
            return 1;
        }
    }
    for (int l = 0; l < 3; l++)
    {
        if (l != line)
        {
            for (int c = 0; c < 3; c++)
            {
                if (get_place_holder(game, l, c) == bot_player_num
                    &&
                    get_piece_size(game, l, c) > not_owned_size)
                {
                    *p_action = MOVE;
                    input1[0] = l;
                    input1[1] = c;
                    input2[0] = line;
                    input2[1] = column;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int try_to_win_vertical(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2], int line, int column)
{
    size not_owned_size = get_piece_size(game, line, column);

    for (size s = not_owned_size + 1; s <= LARGE; s++)
    {
        if (get_nb_piece_in_house(game, bot_player_num, s) > 0)
        {
            *p_action = PLACE;
            input1[0] = s;
            input2[0] = line;
            input2[1] = column;
            return 1;
        }
    }
    for (int l = 0; l < 3; l++)
    {
            for (int c = 0; c < 3; c++)
            {
                if (c != column)
                {
                    if (get_place_holder(game, l, c) == bot_player_num
                        &&
                        get_piece_size(game, l, c) > not_owned_size)
                    {
                        *p_action = MOVE;
                        input1[0] = l;
                        input1[1] = c;
                        input2[0] = line;
                        input2[1] = column;
                        return 1;
                    }
                }
            }
    }
    return 0;
}

int try_to_win_diagonal_down(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2], int line, int column)
{
    size not_owned_size = get_piece_size(game, line, column);

    for (size s = not_owned_size + 1; s <= LARGE; s++)
    {
        if (get_nb_piece_in_house(game, bot_player_num, s) > 0)
        {
            *p_action = PLACE;
            input1[0] = s;
            input2[0] = line;
            input2[1] = column;
            return 1;
        }
    }
    for (int l = 0; l < 3; l++)
    {
            for (int c = 0; c < 3; c++)
            {
                if (c != l){
                    if (get_place_holder(game, l, c) == bot_player_num
                        &&
                        get_piece_size(game, l, c) > not_owned_size)
                    {
                        *p_action = MOVE;
                        input1[0] = l;
                        input1[1] = c;
                        input2[0] = line;
                        input2[1] = column;
                        return 1;
                    }
                }
        }
    }
    return 0;
}

int try_to_win_diagonal_up(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2], int line, int column)
{
    size not_owned_size = get_piece_size(game, line, column);

    for (size s = not_owned_size + 1; s <= LARGE; s++)
    {
        if (get_nb_piece_in_house(game, bot_player_num, s) > 0)
        {
            *p_action = PLACE;
            input1[0] = s;
            input2[0] = line;
            input2[1] = column;
            return 1;
        }
    }
    for (int l = 0; l < 3; l++)
    {
            for (int c = 0; c < 3; c++)
            {
                if (c !=  2-l){
                    if (get_place_holder(game, l, c) == bot_player_num
                        &&
                        get_piece_size(game, l, c) > not_owned_size)
                    {
                        *p_action = MOVE;
                        input1[0] = l;
                        input1[1] = c;
                        input2[0] = line;
                        input2[1] = column;
                        return 1;
                    }
                }
        }
    }
    return 0;
}

int winnable_places(board game, player bot_player_num, int places[8][3])
{
    int line, column;
    int i = 0; //array index

    for (line = 0; line < 3; line++)
    {
        column = two_aligned_in_line(game, line, bot_player_num);
        if (column != -1)
        {
            places[i][0] = line;
            places[i][1] = column;
            places[i][2] = HORIZONTAL;
            i++;
        }
    }

    for (column = 0; column < 3; column++)
    {
        line = two_aligned_in_column(game, column, bot_player_num);
        if (line != -1)
        {
            places[i][0] = line;
            places[i][1] = column;
            places[i][2] = VERTICAL;
            i++;
        }
    }

    for (int y_direction = -1; y_direction <= 1; y_direction += 2)
    {
        if (two_aligned_in_diagonal(game, y_direction, bot_player_num, &column, &line) == 0)
        {
            places[i][0] = line;
            places[i][1] = column;
            places[i][2] = (y_direction + 1) / 2 + DIAGONAL_DOWN;
            i++;
        }
    }

    return i;
}

int two_aligned_in_line(board game, int line, player bot_player_num)
{
    int bot_piece_count = 0;
    int not_owned_place = 0;

	for (int c = 0; c < DIMENSIONS; c++)
	{
		if (get_place_holder(game, line, c) == bot_player_num)
		{
			bot_piece_count++;
		}
        else
        {
            not_owned_place = c;
        }
	}

    if (bot_piece_count == 2)
        return not_owned_place;

    return -1;
}

int two_aligned_in_column(board game, int column, player bot_player_num)
{
    int bot_piece_count = 0;
    int not_owned_place = 0;

	for (int l = 0; l < DIMENSIONS; l++)
	{
		if (get_place_holder(game, l, column) == bot_player_num)
		{
			bot_piece_count++;
		}
        else
        {
            not_owned_place = l;
        }
	}

    if (bot_piece_count == 2)
        return not_owned_place;

    return -1;
}

int two_aligned_in_diagonal(board game, int y_direction, player bot_player_num, int* p_place_x, int* p_place_y)
{
    int bot_piece_count = 0;
	int line, column = 0;

	if (y_direction == 1)
	{
		line = 0;
	}
	else
	{
		line = DIMENSIONS - 1;
	}

	for (int i = 0; i < DIMENSIONS; i++)
	{

		if (get_place_holder(game, line, column) == bot_player_num)
        {
            bot_piece_count++;
        }
        else
        {
            *p_place_x = column;
            *p_place_y = line;
        }

        column += 1;
		line += y_direction;
	}

	if (bot_piece_count == 2)
        return 0;

    return -1;
}*/

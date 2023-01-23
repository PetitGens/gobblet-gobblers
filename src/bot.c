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

int try_to_win(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2])
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
}
#include <stdio.h>

#include "turn.h"
#include "display.h"
#include "board.h"
#include "input.h"

void turn(board game, char player1_name[], char player2_name[])
{	
	int not_valid = 1;
	while(not_valid)
	{
		clear_screen();
		print_board(game);
		printf("\n");
		
		//prints player1's remaining pieces
		change_output_color(BLUE);
		printf("%s's remaining piece(s) :\n", player1_name);
		printf ("×: %d ; X: %d ; ╳: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_1, SMALL),
		get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_1, LARGE));
		
		//prints player2's remaining pieces
		change_output_color(YELLOW);
		printf("%s's remaining piece(s) :\n", player2_name);
		printf ("×: %d ; X: %d ; ╳: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_2, SMALL),
		get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_2, LARGE));
		
		reset_output_color();
		
		//prints next player
		player current_player = next_player(game);
		
		if (current_player == PLAYER_1)
		{
			change_output_color(BLUE);
			printf("%s, it's your turn !\n\n", player1_name);
			reset_output_color();
		}
		else
		{
			change_output_color(YELLOW);
			printf("%s, it's your turn !\n\n", player2_name);
			reset_output_color();
		}
		
		//determines the possible actions for the current player
		enum possible_e possible_action = determine_possible_action(game,
			current_player);
		
		enum action_e action;
		
		//defines the action the player will do, eventually asking him if he has the choice
		if (possible_action == ANY)
		{
			//action choice
			printf("Enter 'p' to place a piece or 'm' to move a piece :\n>");
			action = input_place_move();
			if (action == ERROR)
			{
				error_message("Please enter 'm' or 'p' !");
				continue;
			}
		}
		else if (possible_action == PLACE_ONLY)
		{
			action = PLACE;
		}
		else if (possible_action == MOVE_ONLY)
		{
			action = MOVE;
		}
		
		//lauch the procedure of the right action
		if (action == PLACE)
		{
			if (place(game) == 1)
				not_valid = 0;
		}	
		else if (action == MOVE)
		{
			if (move(game) == 1)
				not_valid = 0;
		}
	}
}

void error_message (const char message[])
{
	printf("%s\n", message);
	printf("Press Enter to continue...");
	getchar();
}

int declare_winner(board* p_game, char player1_name[], char player2_name[])
{
	player winner = get_winner(*p_game);
	if (winner == NO_PLAYER)
	{
		return 1;
	}
	else if (winner == PLAYER_1)
	{
		change_output_color(BLUE);
		printf("%s is the WINNER !!!\n", player1_name);
		reset_output_color();
	}
	else if (winner == PLAYER_2)
	{
		change_output_color(YELLOW);
		printf("%s is the WINNER !!!\n", player2_name);
		reset_output_color();
	}
	int play_again = -1;
	while (play_again == -1)
	{
		printf("Do you want to play again ? ('y' or 'n')\n>");
		play_again = input_yes_no();
	}
	
	*p_game = new_game();
	return play_again;
}

enum possible_e determine_possible_action(board game, player current_player)
{
	int total_pieces = get_nb_piece_in_house(game, current_player, SMALL);
	total_pieces += get_nb_piece_in_house(game, current_player, MEDIUM);
	total_pieces += get_nb_piece_in_house(game, current_player, LARGE);
	
	if (total_pieces == 0)
		return MOVE_ONLY;
	
	for (int line = 0; line < 3; line++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (get_place_holder(game, line, col) == current_player)
				return ANY;
		}
	}
	
	return PLACE_ONLY;
}

int place(board game)
{
	printf("Please enter '1' for a small piece,");
	printf(" '2' for a medium piece or '3' for a large piece :\n");
	printf(">");
	size piece_size = input_piece_size();
	
	if (piece_size == NONE)
	{
		error_message("Please enter a valid digit between 1 and 3 !");
		return 0;
	}
	
	int dest_line, dest_col;
	
	printf("Please enter the destination place as 'XY',");
	printf("where X is the line and Y is the column :\n>");
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -1 || dest_col == -1)
	{
		error_message("Please enter a valid letter followed by a valid digit !");
		return 0;
	}
	
	enum return_code action_return = place_piece(game, piece_size,
		dest_line, dest_col);
	
	switch (action_return)
	{
		case OK:
			return 1;
			break;
		case POSITION:
			error_message("position error !");
			break;
		case SOURCE:
			error_message("You have no more piece of this size left.");
			break;
		case TARGET:
			error_message("You cannot place this piece here !");
			break;
		default:
			error_message("unkown error!");
	}
	return 0;
}

int move (board game)
{
	int src_line, src_col;
	printf("Please enter the position of the piece you want to move");
	printf("as 'XY', where X is the line and Y is the column :\n>");
	input_position(&src_line, &src_col);
	
	if (src_line == -1 || src_col == -1)
	{
		error_message("Please enter a valid letter followed by a valid digit !");
		return 0;
	}
	
	int dest_line, dest_col;
	
	printf("Please enter the destination place as 'XY',");
	printf("where X is the line and Y is the column :\n>");
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -1 || dest_col == -1)
	{
		error_message("Please enter a valid letter followed by a valid digit !");
		return 0;
	}
	
	enum return_code action_return = move_piece(game, src_line,
		src_col, dest_line, dest_col);
		
	switch (action_return)
	{
		case OK:
			return 1;
			break;
		case POSITION:
			error_message("position error !");
			break;
		case SOURCE:
			error_message("There is no piece here, or the upper piece on this place is not yours.");
			break;
		case TARGET:
			error_message("You cannot place this piece here !");
			break;
		default:
			error_message("unkown error!");
	}
	return 0;
}

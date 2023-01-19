#include <stdio.h>

#include "../headers/turn.h"
#include "../headers/display.h"
#include "../headers/board.h"
#include "../headers/input.h"

int turn(board game, char player1_name[], char player2_name[])
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

		printf("You can restart your action at any time by pressing entering 'r'.\n");
		printf("Enter 'q' if you want to quit (you'll be asked if you want to save the current game).\n\n");
		
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
			else if (action == EXIT)
			{
				exit_game(game);
				return 1;
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
			int action_return = place(game);
			if (action_return == 1)
				not_valid = 0;
			else if (action_return == 2)
			{
				printf("Action cancelled.\n");
				printf("Press return to continue...");
				getchar();
				continue;
			}
			else if (action_return == 3)
			{
				exit_game(game);
				return 1;
			}
		}	
		else if (action == MOVE)
		{
			int action_return = move(game);
			if (action_return == 1)
				not_valid = 0;
			else if (action_return == 2)
			{
				printf("Action cancelled.\n");
				printf("Press return to continue...");
				getchar();
				continue;
			}
			else if (action_return == 3)
			{
				exit_game(game);
				return 1;
			}
		}
	}
	return 0;
}

void error_message (const char message[])
{
	printf("%s\n", message);
	printf("Press Return to continue...");
	getchar();
}

int declare_winner(board* p_game, rating ratings[2])
{
	player winner = get_winner(*p_game);
	if (winner == NO_PLAYER)
	{
		return 1;
	}
	if (ratings[0].score == 0 || ratings[1].score == 0)
	{
		load_ratings(ratings);
	}


	clear_screen();
	print_board(*p_game);
	printf("\n");
	if (winner == PLAYER_1)
	{
		calculate_ratings(&ratings[0], &ratings[1]);
		change_output_color(BLUE);
		printf("%s is the WINNER !!!\n", ratings[0].player_name);
		reset_output_color();
	}
	else if (winner == PLAYER_2)
	{
		calculate_ratings(&ratings[1], &ratings[0]);
		change_output_color(YELLOW);
		printf("%s is the WINNER !!!\n", ratings[1].player_name);
		reset_output_color();
	}
	save_rating(&ratings[0]);
	save_rating(&ratings[1]);

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
	else if (piece_size == CANCEL_SIZE)
		return 2;
	else if (piece_size == EXIT_SIZE)
		return 3;
	
	int dest_line = -1, dest_col = -1;
	
	printf("Please enter the destination place as 'XY',");
	printf("where X is the line and Y is the column :\n>");
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -2)
		return 2;
	else if (dest_col == -2)
		return 3;
	else if (dest_line == -1 || dest_col == -1)
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
	int src_line = -1, src_col = -1;
	printf("Please enter the position of the piece you want to move");
	printf("as 'XY', where X is the line and Y is the column :\n>");
	input_position(&src_line, &src_col);
	
	if (src_line == -2)
		return 2;
	else if (src_col == -2)
		return 3;
	if (src_line == -1 || src_col == -1)
	{
		error_message("Please enter a valid letter followed by a valid digit !");
		return 0;
	}
	
	int dest_line = -1, dest_col = -1;
	
	printf("Please enter the destination place as 'XY',");
	printf("where X is the line and Y is the column :\n>");
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -2)
		return 2;
	else if (dest_col == -2)
		return 3;
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

void exit_game(board game)
{
	printf("Exiting game...\n");
	printf("Do you want to save the current game ? (y/n)\n");
	
	int input = -1;

	while(input == -1)
	{
		printf(">");
		input = input_yes_no();
	} 
	if (input == 1)
	{
		printf("Please enter the name of the file you want to write :\n");
		printf(">");
		char filename[FILENAME_MAX_LENGTH];
		input_filename(filename);
		save_game(game, filename);
		printf("Game saved, press return to go back to the main menu...");
		getchar();
	}
}
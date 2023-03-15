#include <stdio.h>
#include <stdlib.h>

#include "../headers/turn.h"
#include "../headers/display.h"
#include "../headers/board.h"
#include "../headers/input.h"
#include "../headers/text.h"

int human_turn(board game, char player1_name[], char player2_name[])
{	
	int not_valid = 1;
	while(not_valid)
	{
		clear_screen();
		print_board(game);
		_printf("\n");
		
		//prints player1's remaining pieces
		change_output_color(BLUE);
		_printf(REMAINING, player1_name);
		
		#ifdef WIN64
		wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_1, SMALL),
		get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_1, LARGE));
		#else
		_printf ("×: %d ; X: %d ; ╳: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_1, SMALL),
		get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_1, LARGE));
		#endif
		
		//prints player2's remaining pieces
		change_output_color(YELLOW);
		_printf(REMAINING, player2_name);

		#ifdef WIN64
		wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_2, SMALL),
		get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_2, LARGE));
		#else
		_printf ("×: %d ; X: %d ; ╳: %d\n\n",
		get_nb_piece_in_house(game, PLAYER_2, SMALL),
		get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
		get_nb_piece_in_house(game, PLAYER_2, LARGE));
		#endif
		
		reset_output_color();
		
		//prints next player
		player current_player = next_player(game);
		
		if (current_player == PLAYER_1)
		{
			change_output_color(BLUE);
			_printf(YOUR_TURN, player1_name);
			reset_output_color();
		}
		else
		{
			change_output_color(YELLOW);
			_printf(YOUR_TURN, player2_name);
			reset_output_color();
		}

		_printf(RESTART_INDICATION);
		_printf(QUIT_INDICATION);
		
		//determines the possible actions for the current player
		enum possible_e possible_action = determine_possible_action(game,
			current_player);
		
		enum action_e action;
		
		//defines the action the player will do, eventually asking him if he has the choice
		if (possible_action == ANY)
		{
			//action choice
			_printf(ACTION_INPUT_PROMPT);
			action = input_place_move();
			if (action == ERROR)
			{
				error_message(ACTION_INPUT_ERROR);
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
				_printf(CANCELLED);
				_printf(PAUSE);
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
				_printf(CANCELLED);
				_printf(PAUSE);
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

void bot_turn(board game, char player1_name[], char player2_name[], bot_difficulty_e bot_dif)
{
	clear_screen();
	print_board(game);
	_printf("\n");
	
	//prints player1's remaining pieces
	change_output_color(BLUE);
	_printf(REMAINING, player1_name);
	
	#ifdef WIN64
	wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_1, SMALL),
	get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_1, LARGE));
	#else
	_printf ("×: %d ; X: %d ; ╳: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_1, SMALL),
	get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_1, LARGE));
	#endif
	
	//prints player2's remaining pieces
	change_output_color(YELLOW);
	_printf(REMAINING, player2_name);
	
	#ifdef WIN64
	wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_2, SMALL),
	get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_2, LARGE));
	#else
	_printf ("×: %d ; X: %d ; ╳: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_2, SMALL),
	get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_2, LARGE));
	#endif
	
	reset_output_color();
	
	//prints next player
	player current_player = next_player(game);

	char turn_message[64];
	
	if (current_player == PLAYER_1)
	{
		change_output_color(BLUE);
		_printf(BOT_THINKING, player1_name, player1_name);
		reset_output_color();
		
		bot_play(game, current_player, bot_dif, player1_name, turn_message);
	}
	else
	{
		change_output_color(YELLOW);
		_printf(BOT_THINKING, player2_name, player2_name);
		reset_output_color();

		bot_play(game, current_player, bot_dif, player2_name, turn_message);
	}

	

	clear_screen();
	print_board(game);
	_printf("\n");
	
	//prints player1's remaining pieces
	change_output_color(BLUE);
	_printf(REMAINING, player1_name);

	
	#ifdef WIN64
	wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_1, SMALL),
	get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_1, LARGE));
	#else
	_printf ("×: %d ; X: %d ; ╳: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_1, SMALL),
	get_nb_piece_in_house(game, PLAYER_1, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_1, LARGE));
	#endif
	
	//prints player2's remaining pieces
	change_output_color(YELLOW);
	_printf(REMAINING, player2_name);
	
	#ifdef WIN64
	wprintf (L"\x00d7: %d ; X: %d ; \x2573: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_2, SMALL),
	get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_2, LARGE));
	#else
	_printf ("×: %d ; X: %d ; ╳: %d\n\n",
	get_nb_piece_in_house(game, PLAYER_2, SMALL),
	get_nb_piece_in_house(game, PLAYER_2, MEDIUM),
	get_nb_piece_in_house(game, PLAYER_2, LARGE));
	#endif
	
	reset_output_color();
	
	if (current_player == PLAYER_1)
	{
		change_output_color(BLUE);
		_printf(BOT_THINKING, player1_name, player1_name);
		reset_output_color();
	}
	else
	{
		change_output_color(YELLOW);
		_printf(BOT_THINKING, player2_name, player2_name);
		reset_output_color();
	}

	_printf("\n%s\n", turn_message);
	_printf(PAUSE);
	getchar();
}

void error_message (const char message[])
{
	_printf("%s\n", message);
	_printf(PAUSE);
	getchar();
}

int declare_winner_rating(board* p_game, rating ratings[2])
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
	_printf("\n");
	if (winner == PLAYER_1)
	{
		calculate_elo_ratings(&ratings[0], &ratings[1]);
		change_output_color(BLUE);
		_printf(WINNER, ratings[0].player_name);
		reset_output_color();
	}
	else if (winner == PLAYER_2)
	{
		calculate_elo_ratings(&ratings[1], &ratings[0]);
		change_output_color(YELLOW);
		_printf(WINNER, ratings[1].player_name);
		reset_output_color();
	}
	save_rating(&ratings[0]);
	save_rating(&ratings[1]);

	int play_again = -1;
	while (play_again == -1)
	{
		_printf(PLAY_AGAIN);
		play_again = input_yes_no();
	}
	
	*p_game = new_game();
	return play_again;
}

int declare_winner_no_rating(board* p_game, char player1_name[], char player2_name[])
{
	player winner = get_winner(*p_game);
	if (winner == NO_PLAYER)
	{
		return 1;
	}


	clear_screen();
	print_board(*p_game);
	_printf("\n");
	if (winner == PLAYER_1)
	{
		change_output_color(BLUE);
		_printf(WINNER, player1_name);
		reset_output_color();
	}
	else if (winner == PLAYER_2)
	{
		change_output_color(YELLOW);
		_printf(WINNER, player2_name);
		reset_output_color();
	}

	int play_again = -1;
	while (play_again == -1)
	{
		_printf(PLAY_AGAIN);
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
	_printf(SIZE_INPUT_PROMPT);
	size piece_size = input_piece_size();
	
	if (piece_size == NONE)
	{
		error_message(SIZE_INPUT_ERROR);
		return 0;
	}
	else if (piece_size == CANCEL_SIZE)
		return 2;
	else if (piece_size == EXIT_SIZE)
		return 3;
	
	int dest_line = -1, dest_col = -1;
	
	_printf(DEST_INPUT_PROMPT);
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -2)
		return 2;
	else if (dest_col == -2)
		return 3;
	else if (dest_line == -1 || dest_col == -1)
	{
		error_message(POS_INPUT_ERROR);
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
			error_message(POS_ERROR);
			break;
		case SOURCE:
			error_message(PLACE_SRC_ERROR);
			break;
		case TARGET:
			error_message(PLACE_DEST_ERROR);
			break;
		default:
			error_message("[unkown error!]");
	}
	return 0;
}

int move (board game)
{
	int src_line = -1, src_col = -1;
	_printf(SRC_INPUT_PROMPT);
	input_position(&src_line, &src_col);
	
	if (src_line == -2)
		return 2;
	else if (src_col == -2)
		return 3;
	if (src_line == -1 || src_col == -1)
	{
		error_message(POS_INPUT_ERROR);
		return 0;
	}
	
	int dest_line = -1, dest_col = -1;
	
	_printf(DEST_INPUT_PROMPT);
	input_position(&dest_line, &dest_col);
	
	if (dest_line == -2)
		return 2;
	else if (dest_col == -2)
		return 3;
	if (dest_line == -1 || dest_col == -1)
	{
		error_message(POS_INPUT_ERROR);
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
			error_message(POS_ERROR);
			break;
		case SOURCE:
			error_message(MOVE_SRC_ERROR);
			break;
		case TARGET:
			error_message(MOVE_DEST_ERROR);
			break;
		default:
			error_message("[unkown error!]");
	}
	return 0;
}

void exit_game(board game)
{
	_printf(EXITING);
	_printf(SAVE_PROMPT);
	
	int input = -1;

	while(input == -1)
	{
		_printf(">");
		input = input_yes_no();
	} 
	if (input == 1)
	{
		_printf(FILENAME_WRITE_PROMPT);
		char filename[FILENAME_MAX_LENGTH];
		input_filename(filename);
		save_game(game, filename);
		_printf(SAVED);
		getchar();
	}
}
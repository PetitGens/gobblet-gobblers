#include <stdio.h>
#include <stdlib.h>
#include "../headers/board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author Julien AIT AZZOUZENE, Ewan CANTON
 */

/**
 * @brief The board of the game.
 */

typedef struct
{
	size p_size;
	player p_player;
} piece;

typedef struct 
{
	piece pieces_stack[NB_SIZE];
	int piece_number;
} square;

struct board_s
{
	square squares[DIMENSIONS*DIMENSIONS];
	int houses[NB_PLAYERS][NB_SIZE];
	player current_player;
};

board new_game(){
	board new_board = malloc(sizeof(struct board_s));

	for (int p = 0; p < NB_PLAYERS; p++)
	{
		for (int s = 0; s < NB_SIZE; s++)
		{
			new_board->houses[p][s] = NB_INITIAL_PIECES;
		}
	}

	for (int i = 0; i < DIMENSIONS*DIMENSIONS; i++)
	{
		square current_square;
		current_square.piece_number = 0;

		new_board->squares[i] = current_square;
	}

	if (FIRST_PLAYER == RANDOM)
	{
		new_board->current_player = rand() % NB_PLAYERS + 1;
	}
	else
	{
		new_board->current_player = FIRST_PLAYER;
	}
		

	return new_board;
}

board copy_game(board original_game){
	board new_board = malloc(sizeof(struct board_s));

	for (int p = 0; p < NB_PLAYERS; p++)
	{
		for (int s = 0; s < NB_SIZE; s++)
		{
			new_board->houses[p][s] = original_game->houses[p][s];
		}
	}

	for (int i = 0; i < DIMENSIONS*DIMENSIONS; i++)
	{
		square current_square;
		square original_square = original_game->squares[i];
		current_square.piece_number = original_square.piece_number;

		for (int j = 0; j < current_square.piece_number; j++)
		{
			piece current_piece = {original_square.pieces_stack[j].p_size, original_square.pieces_stack[j].p_player};
			current_square.pieces_stack[j] = current_piece;
		}

		new_board->squares[i] = current_square;
	}

	new_board->current_player = original_game->current_player;

	return new_board;
}

void destroy_game(board game){
	free(game);
}

player next_player(board game)
{
	return game->current_player;
}

player get_place_holder(board game, int line, int column)
{
    if (line < 0 || line >= DIMENSIONS) return 0;
	if (column < 0 || column >= DIMENSIONS) return 0;
    
	int square_index = line * DIMENSIONS + column;

	int square_piece_number = game->squares[square_index].piece_number;

	if (square_piece_number == 0)
		return NO_PLAYER;

	return game->squares[square_index].pieces_stack[square_piece_number-1].p_player;
}

size get_piece_size(board game, int line, int column)
{
    if (line < 0 || line >= DIMENSIONS) return 0;
	if (column < 0 || column >= DIMENSIONS) return 0;
    
	int square_index = line * DIMENSIONS + column;

	int square_piece_number = game->squares[square_index].piece_number;

	if (square_piece_number == 0)
		return NO_PLAYER;

	return game->squares[square_index].pieces_stack[square_piece_number-1].p_size;
}

player horizontal_winner_check(board game, int line)
{
	player line_pieces[DIMENSIONS];

	line_pieces[0] = get_place_holder(game, line, 0);

	for (int c = 1; c < DIMENSIONS; c++)
	{
		line_pieces[c] = get_place_holder(game, line, c);
		if (line_pieces[c] != line_pieces[c-1])
		{
			return NO_PLAYER;
		}
	}

	return line_pieces[0];
}

player vertical_winner_check(board game, int column)
{
	player col_pieces[DIMENSIONS];

	col_pieces[0] = get_place_holder(game, 0, column);

	for (int l = 1; l < DIMENSIONS; l++)
	{
		col_pieces[l] = get_place_holder(game, l, column);
		if (col_pieces[l] != col_pieces[l-1])
		{
			return NO_PLAYER;
		}
	}

	return col_pieces[0];
}

player diagonal_check(board game, int y_direction)
{
	player diag_pieces[DIMENSIONS];
	int line, column = 0;

	if (y_direction == 1)
	{
		line = 0;
	}
	else
	{
		line = DIMENSIONS - 1;
	}

	diag_pieces[0] = get_place_holder(game, line, column);


	for (int i = 1; i < DIMENSIONS; i++)
	{
		column += 1;
		line += y_direction;

		diag_pieces[i] = get_place_holder(game, line, column);
		if (diag_pieces[i] != diag_pieces[i-1])
		{
			return NO_PLAYER;
		}
	}

	return diag_pieces[0];
}

player get_winner(board game)
{
	bool alignment [NB_PLAYERS] = {false};

	for (int i = 0; i < DIMENSIONS; i++)
	{
		player line_check = horizontal_winner_check(game, i);

		if (line_check != NO_PLAYER)
		{
			alignment[line_check - 1] = true;
		}

		player col_check = vertical_winner_check(game, i);

		if (col_check != NO_PLAYER)
		{
			alignment[col_check - 1] = true;
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		player diag_check = diagonal_check(game, i);

		if (diag_check != NO_PLAYER)
		{
			alignment[diag_check - 1] = true;
		}
	}

	int nb_winner = 0;
	player winner;
	for (int p = 0; p < NB_PLAYERS; p++)
	{
		if (alignment[p] == true)
		{
			nb_winner++;
			winner = p + 1;
		}
	}

	if (nb_winner == 1)
	{
		return winner;
	}

	return NO_PLAYER;
}

int get_nb_piece_in_house(board game, player checked_player, size piece_size)
{
    if (checked_player > NB_PLAYERS) return 0;
	if (piece_size > NB_SIZE) return 0;
	if (checked_player <= 0) return 0;
	if (piece_size <= 0) return 0;
    
	return game->houses[checked_player - 1][piece_size - 1];
}

void switch_player(board game)
{
	game->current_player = game->current_player % NB_PLAYERS + 1;
}

enum return_code is_placement_possible(board game, size piece_size, int line, int column)
{
	if (
		line < 0
		|| line >= DIMENSIONS
		|| column < 0
		|| column >= DIMENSIONS
		)
	{
		return POSITION;
	}

	if ( get_nb_piece_in_house(game, next_player(game), piece_size) <= 0 )
		return SOURCE;

	if ( piece_size <= get_piece_size(game, line, column) )
		return TARGET;

	return OK;
}

enum return_code place_piece(board game, size piece_size, int line, int column)
{
	enum return_code return_code = is_placement_possible(game, piece_size, line, column);

	if (return_code != OK)
		return return_code;

	int square_nb_pieces = game->squares[line * DIMENSIONS + column].piece_number;
	piece piece_to_place = {piece_size, next_player(game)};

	game->squares[line * DIMENSIONS + column].pieces_stack[square_nb_pieces] = piece_to_place;
	game->squares[line * DIMENSIONS + column].piece_number ++;

	game->houses[next_player(game) - 1][piece_size - 1] --;

	switch_player(game);

	return OK;
}

enum return_code is_movement_possible(board game, int source_line, int source_column, int target_line, int target_column)
{
	if (
		source_line < 0
		|| source_line >= DIMENSIONS
		|| source_column < 0
		|| source_column >= DIMENSIONS
		|| target_line < 0
		|| target_line >= DIMENSIONS
		|| target_column < 0
		|| target_column >= DIMENSIONS
		)
	{
		return POSITION;
	}

	if ( get_place_holder(game, source_line, source_column) != next_player(game) )
		return SOURCE;
	
	if ( get_piece_size(game, source_line, source_column) <= get_piece_size(game, target_line, target_column) )
		return TARGET;

	return OK;
}

enum return_code move_piece(board game, int source_line, int source_column, int target_line, int target_column)
{
	enum return_code return_code = is_movement_possible(game, source_line, source_column, target_line, target_column);

	if (return_code != OK)
		return return_code;

	int target_nb_pieces = game->squares[target_line * DIMENSIONS + target_column].piece_number;
	piece piece_to_place = {get_piece_size(game, source_line, source_column), next_player(game)};

	game->squares[target_line * DIMENSIONS + target_column].pieces_stack[target_nb_pieces] = piece_to_place;
	game->squares[target_line * DIMENSIONS + target_column].piece_number ++;

	game->squares[source_line * DIMENSIONS + source_column].piece_number --;

	switch_player(game);

	return OK;
}

board load_game(char * filename)
{
	FILE * stream = fopen(filename, "r");
	if (stream == NULL)
	{
		//printf("erreur d'ouverture du fichier\n");
		return NULL;
	}

	board game = new_game();

	char input = 0;
	game->current_player = 0;
	do
	{
		if (fscanf(stream, "%c", &input) == EOF)
		{
			//printf("fin prématurée du fichier\n");
			return NULL;
		}

		if (input != '\n')
		{
			if (input < '0' || input > '9')
			{
				//printf("caractère inattendu rencontré : %c\n", input);
				return NULL;
			}

			game->current_player *= 10;
			game->current_player += (unsigned int)input - '0';
		}
	} while(input != '\n');

	for (int p = 0; p < NB_PLAYERS; p++)
	{
		for (int s = 0; s < NB_SIZE; s++)
		{
			game->houses[p][s] = 0;
			do
			{
				if (fscanf(stream, "%c", &input) == EOF)
				{
					//printf("fin prématurée du fichier\n");
					return NULL;
				}

				if (input != '\n' && input != ',')
				{
					if (input < '0' || input > '9')
					{
						//printf("caractère inattendu rencontré : %c\n", input);
						return NULL;
					}

					game->houses[p][s] *= 10;
					game->houses[p][s] += input - '0';
				}
			} while(input != '\n' && input != ',');
		}
	}

	for (int i = 0; i < DIMENSIONS*DIMENSIONS; i++)
	{
		int nb_pieces = 0;
		do
		{
			nb_pieces++;
			player holder = 0;
			size piece_size = 0;

			do
			{
				if (fscanf(stream, "%c", &input) == EOF)
				{
					input = '\n';
				}

				if (input != ',' && input != 'v' && input != '\n')
				{
					if (input < '0' || input > '9')
					{
						//printf("caractère inattendu rencontré : %c\n", input);
						return NULL;
					}

					holder *= 10;
					holder += (unsigned int)input - '0';
				}
			} while(input != ',' && input != 'v' && input != '\n');

			if (input != 'v')
			{
				do
				{
					if (fscanf(stream, "%c", &input) == EOF)
					{
						input ='\n';
					}

					if (input != ';' && input != '\n')
					{
						if (input < '0' || input > '9')
						{
							//printf("caractère inattendu rencontré : %c\n", input);
							return NULL;
						}

						piece_size *= 10;
						piece_size += (unsigned int)input - '0';
					}
				} while(input != ';' && input != '\n');

				piece current_piece = {piece_size, holder};
				game->squares[i].pieces_stack[nb_pieces - 1] = current_piece;
			}

			else
			{
				nb_pieces = 0;
				if (fscanf(stream, "%c", &input) == EOF)
				{
					input ='\n';
				}
			}			
		} while (input != '\n');

		game->squares[i].piece_number = nb_pieces;
	}

	return game;
}

void save_game(board game, char * filename)
{
	FILE* stream = fopen(filename, "w");
	if (stream == NULL)
		return;

	fprintf(stream, "%d\n", next_player(game));

	for (int p = 0; p < NB_PLAYERS; p++)
	{
		for (int s = 0; s < NB_SIZE; s++)
		{
			if (s > 0)
			{
				fprintf(stream, ",");
			}
			fprintf(stream, "%d", game->houses[p][s]);
		}
		fprintf(stream, "\n");
	}

	for (int s = 0; s < DIMENSIONS * DIMENSIONS; s++)
	{
		if (s > 0)
		{
			fprintf(stream, "\n");
		}
		for (int p = 0; p < game->squares[s].piece_number; p++)
		{
			if (p > 0)
			{
				fprintf(stream, ";");
			}
			fprintf(stream, "%d,%d", game->squares[s].pieces_stack[p].p_player, game->squares[s].pieces_stack[p].p_size);
		}
		if (game->squares[s].piece_number == 0)
		{
			fprintf(stream, "v");
		}
	}

	fclose(stream);
}
#ifdef DEBUG
int board_size()
{
	return (int)sizeof(struct board_s);
}
#endif
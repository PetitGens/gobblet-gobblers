#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN64
#include <fcntl.h>
#include <io.h>
#endif

#include "../headers/display.h"
#include "../headers/action.h"
#include "../headers/text.h"
#include <string.h>

void clear_screen()
{
	#ifndef DEBUG
	_printf("\033[H\033[2J");
	#endif
}

void change_output_color(enum color_e color)
{
	_printf("\033[3%dm", color);
}

void reset_output_color()
{
	_printf("\033[0m");
}

void print_board(board game)
{
	_printf("     1     2     3\n");
	
	//prints a first line of '_'
	_printf("   _________________\n");
	
	//each iteration prints a line of 3 squares of the board
	for (int line = 0; line < 3; line++)
	{
		//fist line
		_printf("  |     |     |     |\n");
		
		//second line, including each pieces
		switch (line)
		{
			case 0:
				_printf("A ");
				break;
			case 1:
				_printf("B ");
				break;
			case 2:
				_printf("C ");
		}
		
		_printf("|  ");
		for (int col = 0; col < 3; col++)
		{
			#ifdef WIN64
			wchar_t piece;
			insert_piece(&piece, game, line, col);
			_printf("%lc", piece);
			#else
			char piece[5];
			insert_piece(piece, game, line, col);
			_printf("%s", piece);
			#endif
			reset_output_color();
			_printf("  |  ");
		}
		_printf("\n");
		
		//third line
		_printf("  |_____|_____|_____|\n");
	} 
}
#ifdef WIN64
void insert_piece(wchar_t *piece, board game, int line, int col)
{
		player holder = get_place_holder(game, line, col);
		
		if (holder == NO_PLAYER)
		{		
				*piece = ' ';
				return;
		}
		
		size piece_size = get_piece_size(game, line, col);
		
		if (holder == PLAYER_1)
		{
			change_output_color(BLUE);
			
		}
		else if (holder == PLAYER_2)
		{
			change_output_color(YELLOW);
		}
		
		switch (piece_size)
		{
			case SMALL:
				//strcpy(piece, "×");
				*piece = 0x00d7;
				break;
			case MEDIUM:
				*piece = 'x';
				break;
			case LARGE:
				//strcpy(piece, "╳");
				*piece = 0x2573;
				break;
			default:
				*piece = ' ';	
		}
}
#else
void insert_piece(char piece[], board game, int line, int col)
{
		player holder = get_place_holder(game, line, col);
		
		if (holder == NO_PLAYER)
		{
				#ifdef WIN64
				
				#else
				piece[0] = ' ';
				piece[1] = '\0';
				#endif
				return;
		}
		
		size piece_size = get_piece_size(game, line, col);
		
		if (holder == PLAYER_1)
		{
			change_output_color(BLUE);
			
		}
		else if (holder == PLAYER_2)
		{
			change_output_color(YELLOW);
		}
		
		switch (piece_size)
		{
			case SMALL:
				strcpy(piece, "×");
				break;
			case MEDIUM:
				piece[0] = 'X';
				piece[1] = '\0';
				break;
			case LARGE:
				strcpy(piece, "╳");
				break;
			default:
				piece[0] = ' ';
				piece[1] = '\0';	
		}
}
#endif

void print_leaderboard(rating ratings[MAX_NB_RATINGS], int nb_ratings)
{
	int width = 10 + 4 + NAME_MAX_LENGTH + 11; // Total width of the leaderboard as it is displayed
	for (int i = 0; i < width; i++)
		_printf("-");
	_printf("\n");

	#if LANGUAGE == ENGLISH
	_printf("|  RANK  |  NAME");
	#elif LANGUAGE == FRENCH
	_printf("|  RANG  |  NOM ");
	#endif
	for (int i = 0; i < NAME_MAX_LENGTH - 3; i++)
		_printf(" ");
	_printf("|  SCORE  |\n");

	_printf("|--------|---------------------------------|---------|\n");

	for (int i = 0; i < nb_ratings; i++)
	{
		_printf("|  %4d  ", i + 1);

		char name_copy [NAME_MAX_LENGTH];
		strcpy(name_copy, ratings[i].player_name);
		format_name_for_leaderboard(name_copy);
		_printf("|  %s  ", name_copy);
		_printf("|  %5d  |\n", ratings[i].score);
	}

	for (int i = 0; i < width; i++)
		_printf("-");
	_printf("\n");
}

void format_name_for_leaderboard(char name[NAME_MAX_LENGTH])
{
	for (int i = (int)strlen(name); i < NAME_MAX_LENGTH - 1; i++)
	{
		name[i] = ' ';
	}
	name[NAME_MAX_LENGTH - 1] = '\0';
}

void bot_turn_message(char message[], char bot_name[], enum action_e action, int input1[2], int input2[2])
{
	char dest[3];
	dest[0] = (char)('A' + input2[0]); 
	dest[1] = (char)('1' + input2[1]);
	dest[2] = '\0';


	if (action == PLACE)
	{
		char piece_size[32] = "";
		switch (input1[0])
		{
			case SMALL:
				strcpy(piece_size, SIZE_1);
				break;
			case MEDIUM:
				strcpy(piece_size, SIZE_2);
				break;
			case LARGE:
				strcpy(piece_size, SIZE_3);
				break;
			default:
				strcpy(piece_size, "[invalid size]");
		}

		sprintf(message, BOT_PLACING_MSG, bot_name, piece_size, dest);
	}
	else if (action == MOVE)
	{
		char src[3];
		src[0] = (char)('A' + input1[0]); 
		src[1] = (char)('1' + input1[1]);
		src[2] = '\0';

		sprintf(message, BOT_MOVING_MSG, bot_name, src, dest);
	}
	else{
		strcpy(message, "error, invalid action\n");
	}
}

int _printf(const char* format, ...)
{
	#ifdef _WIN64
	wchar_t text[TEXT_MAX_SIZE];
	mbstowcs(text, format, TEXT_MAX_SIZE);
	va_list args;
	va_start(args, format);
	int value = vwprintf(text, args);
	va_end(args);
	return value;
	#else

	va_list args;
	va_start(args, format);
	int value = vprintf(format, args);
	va_end(args);
	return value;

	#endif
}
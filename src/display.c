#include <stdio.h>

#include "../headers/display.h"
#include "../headers/board.h"
#include "../headers/input.h"
#include <string.h>

void clear_screen()
{
	#ifndef DEBUG
	printf("\033[H\033[2J");
	#endif
}

void change_output_color(enum color_e color)
{
	printf("\033[3%dm", color);
}

void reset_output_color()
{
	printf("\033[0m");
}

void print_board(board game)
{
	printf("     1     2     3\n");
	
	//prints a first line of '_'
	printf("   _________________\n");
	
	//each iteration prints a line of 3 squares of the board
	for (int line = 0; line < 3; line++)
	{
		//fist line
		printf("  |     |     |     |\n");
		
		//second line, including each pieces
		switch (line)
		{
			case 0:
				printf("A ");
				break;
			case 1:
				printf("B ");
				break;
			case 2:
				printf("C ");
		}
		
		printf("|  ");
		for (int col = 0; col < 3; col++)
		{
			char piece[5];
			insert_piece(piece, game, line, col);
			printf("%s", piece);
			reset_output_color();
			printf("  |  ");
		}
		printf("\n");
		
		//third line
		printf("  |_____|_____|_____|\n");
	} 
}

void insert_piece(char piece[], board game, int line, int col)
{
		player holder = get_place_holder(game, line, col);
		
		if (holder == NO_PLAYER)
		{
				piece[0] = ' ';
				piece[1] = '\0';
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

void print_leaderboard(rating ratings[MAX_NB_RATINGS], int nb_ratings)
{
	int width = 10 + 4 + NAME_MAX_LENGTH + 11; // Total width of the leaderboard as it is displayed
	for (int i = 0; i < width; i++)
		printf("-");
	printf("\n");

	printf("|  RANK  |  NAME");
	for (int i = 0; i < NAME_MAX_LENGTH - 3; i++)
		printf(" ");
	printf("|  SCORE  |\n");

	printf("|--------|---------------------------------|---------|\n");

	for (int i = 0; i < nb_ratings; i++)
	{
		printf("|  %4d  ", i + 1);

		char name_copy [NAME_MAX_LENGTH];
		strcpy(name_copy, ratings[i].player_name);
		format_name_for_leaderboard(name_copy);
		printf("|  %s  ", name_copy);
		printf("|  %5d  |\n", ratings[i].score);
	}

	for (int i = 0; i < width; i++)
		printf("-");
	printf("\n");
}

void format_name_for_leaderboard(char name[NAME_MAX_LENGTH])
{
	for (int i = (int)strlen(name); i < NAME_MAX_LENGTH - 1; i++)
	{
		name[i] = ' ';
	}
	name[NAME_MAX_LENGTH - 1] = '\0';
}

void bot_turn_message(char message[], char bot_name[],enum action_e action, int input1[2], int input2[2])
{
	char dest[3];
	dest[0] = 'A' + (char)input2[0]; 
	dest[1] = '1' + (char)input2[1];
	dest[2] = '\0';


	if (action == PLACE)
	{
		char piece_size[32] = "";
		switch (input1[0])
		{
			case SMALL:
				strcpy(piece_size, "small");
				break;
			case MEDIUM:
				strcpy(piece_size, "medium");
				break;
			case LARGE:
				strcpy(piece_size, "large");
				break;
			default:
				strcpy(piece_size, "[invalid size]");
		}

		sprintf(message, "%s placed a %s piece at %s.", bot_name, piece_size, dest);
	}
	else if (action == MOVE)
	{
		char src[3];
		src[0] = 'A' + (char)input1[0]; 
		src[1] = '1' + (char)input1[1];
		src[2] = '\0';

		sprintf(message, "%s moved a piece from %s to %s.", bot_name, src, dest);
	}
	else{
		strcpy(message, "error, invalid action\n");
	}
}
#include <stdio.h>

#include "display.h"
#include "board.h"
#include "string.h"

void clear_screen()
{
	printf("\033[H\033[2J");
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

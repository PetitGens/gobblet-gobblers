#include <stdio.h>

#include "input.h"
#include "board.h"

void input_players_names(char name1[], char name2[])
{
	printf("Please enter the first player's name.\n>");
	fgets(name1, NAME_MAX_LENGTH - 1, stdin);
	printf("Please enter the second player's name.\n>");
	fgets(name2, NAME_MAX_LENGTH - 1, stdin);
}

void delete_carriage_return (char string[])
{
	int i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
		{
			string[i] = '\0';
			return;
		}
		i++;
	}
}

enum action_e input_place_move()
{
	char choice = 0;
	scanf("%c", &choice);
		
	char buffer;
	do
	{
		scanf("%c", &buffer);
	} while(buffer != '\n');
	
	if (choice == 'p') return PLACE;
	else if (choice == 'm') return MOVE;
	
	return ERROR;
}

size input_piece_size()
{
	char choice = 0;
	scanf("%c", &choice);
		
	char buffer;
	do
	{
		scanf("%c", &buffer);
	} while(buffer != '\n');
	
	if (choice == '1') return SMALL;
	else if (choice == '2') return MEDIUM;
	else if (choice == '3') return LARGE;
	
	return NONE;
}

void input_position (int* p_line, int* p_col)
{
	char choice[3];
	scanf("%c", &choice[0]);
	scanf("%c", &choice[1]);
	choice[2] = '\0';
	
	char buffer;
	do
	{
		scanf("%c", &buffer);
	} while(buffer != '\n');
	
	if (choice[0] >= 'A' && choice[0] <= 'C')
	{
		*p_line = (int) (choice[0] - 'A');
	}
	else if (choice[0] >= 'a' && choice[0] <= 'c')
	{
		*p_line = (int) (choice[0] - 'a');
	}
	else
	{
		*p_line = -1;
		return;
	}
	
	if (choice[1] >= '1' && choice[1] <= '3')
	{
		*p_col = (int) (choice[1] - '1');
	}
	else *p_col = -1;
}

int input_yes_no()
{
	char choice = 0;
	scanf("%c", &choice);
		
	char buffer;
	do
	{
		scanf("%c", &buffer);
	} while(buffer != '\n');
	
	if (choice == 'y')
		return 1;
		
	if (choice == 'n')
		return 0;
		
	return -1;
}

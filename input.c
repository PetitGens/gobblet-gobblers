#include <stdio.h>
#include <string.h>

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
	
	if (choice == 'p' || choice == 'P') return PLACE;
	else if (choice == 'm' || choice == 'M') return MOVE;
	else if (choice == 'q' || choice == 'Q') return EXIT;
	
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
	
	else if (choice == 'r' || choice == 'R') return CANCEL_SIZE;
	else if (choice == 'q' || choice == 'Q') return EXIT_SIZE;
	
	return NONE;
}

void input_position (int* p_line, int* p_col)
{
	char choice[2];
	scanf("%c", &choice[0]);

	if (choice[0] == 'r' || choice[0] == 'R')
	{
		*p_line = -2;
		char buffer;
		do
		{
			scanf("%c", &buffer);
		} while(buffer != '\n');
		return;
	}
	if (choice[0] == 'q' || choice[0] == 'Q')
	{
		*p_col = -2;
		char buffer;
		do
		{
			scanf("%c", &buffer);
		} while(buffer != '\n');
		return;
	}

	scanf("%c", &choice[1]);
	
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

menu_choice input_main_menu()
{
	char choice[CHOICE_MAX_LENGTH];
	fgets(choice, CHOICE_MAX_LENGTH - 1, stdin);

	delete_carriage_return(choice);

	if (strcmp(choice, "help") == 0)
		return HELP;

	else if (strcmp(choice, "pvp") == 0)
		return PVP;

	else if (strcmp(choice, "load-pvp") == 0)
		return LOAD_PVP;

	else if (strcmp(choice, "quit") == 0)
		return QUIT;

	else
		return NONE;
}

void input_filename(char filename[FILENAME_MAX_LENGTH])
{
	do
	{
		fgets(filename, FILENAME_MAX_LENGTH - 1, stdin);
    	delete_carriage_return(filename);
	} while(filename[0] == '\0');
}
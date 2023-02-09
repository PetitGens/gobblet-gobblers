#include <stdio.h>
#include <string.h>

#include "../headers/input.h"
#include "../headers/board.h"

void input_players_names(char name1[], char name2[])
{
	printf("Please enter the first player's name.\n>");
	if (fgets(name1, NAME_MAX_LENGTH - 1, stdin) == NULL)
		printf("Error in name input.\n");
	printf("Please enter the second player's name.\n>");
	if (fgets(name2, NAME_MAX_LENGTH - 1, stdin) == NULL)
		printf("Error in name input.\n");
}

void input_single_player_name(char name[])
{
	printf("Please enter your name.\n>");
	if (fgets(name, NAME_MAX_LENGTH - 1, stdin) == NULL)
		printf("Error in name input.\n");
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
	do ;
	while(scanf("%c", &choice) <= 0);
		
	char buffer;
	do
	{
		if (scanf("%c", &buffer) <= 0);
	} while(buffer != '\n');
	
	if (choice == 'p' || choice == 'P') return PLACE;
	else if (choice == 'm' || choice == 'M') return MOVE;
	else if (choice == 'q' || choice == 'Q') return EXIT;
	
	return ERROR;
}

size input_piece_size()
{
	char choice = 0;
	do ;
	while(scanf("%c", &choice) <= 0);
		
	char buffer;
	do
	{
		if (scanf("%c", &buffer) <= 0);
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
	do ;
	while (scanf("%c", &choice[0]) <= 0);

	if (choice[0] == 'r' || choice[0] == 'R')
	{
		*p_line = -2;
		char buffer;
		do
		{
			if (scanf("%c", &buffer) <= 0);
		} while(buffer != '\n');
		return;
	}
	if (choice[0] == 'q' || choice[0] == 'Q')
	{
		*p_col = -2;
		char buffer;
		do
		{
			if (scanf("%c", &buffer) <= 0);
		} while(buffer != '\n');
		return;
	}

	do;
	while (scanf("%c", &choice[1]) <= 0);
	
	char buffer;
	do
	{
		if (scanf("%c", &buffer) <= 0);
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
	do ;
	while(scanf("%c", &choice) <= 0);
		
	char buffer;
	do
	{
		if (scanf("%c", &buffer) <= 0);
	} while(buffer != '\n');
	
	if (choice == 'y' || choice == 'Y')
		return 1;
		
	if (choice == 'n' || choice == 'N')
		return 0;
		
	return -1;
}

menu_choice input_main_menu()
{
	char choice[CHOICE_MAX_LENGTH];
	if (fgets(choice, CHOICE_MAX_LENGTH - 1, stdin) == NULL)
		printf("Error in menu input.\n");

	delete_carriage_return(choice);

	if (strcmp(choice, "help") == 0)
		return HELP;

	else if (strcmp(choice, "pvp") == 0)
		return PVP;

	else if (strcmp(choice, "load-pvp") == 0)
		return LOAD_PVP;

	else if (strcmp(choice, "pvb") == 0)
		return PVB;

	else if (strcmp(choice, "load-pvb") == 0)
		return LOAD_PVB;

	else if (strcmp(choice, "bvb") == 0)
		return BVB;

	else if (strcmp(choice, "load-bvb") == 0)
		return LOAD_BVB;

	else if (strcmp(choice, "quit") == 0)
		return QUIT;

	else if (strcmp(choice, "leaderboard") == 0)
		return LEADERBOARD;

	else
		return NONE;
}

void input_filename(char filename[FILENAME_MAX_LENGTH])
{
	do
	{
		if (fgets(filename, CHOICE_MAX_LENGTH - 1, stdin) == NULL)
			printf("Error in menu input.\n");
    	delete_carriage_return(filename);
	} while(filename[0] == '\0');
}

bot_difficulty_e input_bot_difficulty()
{
	char choice = 0;
	do ;
	while(scanf("%c", &choice) <= 0);
		
	char buffer;
	do
	{
		if (scanf("%c", &buffer) <= 0);
	} while(buffer != '\n');

	if (choice == '1') return EASY;
	else if (choice == '2') return MEDIUM_DIFF;
	else if (choice == '3') return HARD;

	return -1;
}

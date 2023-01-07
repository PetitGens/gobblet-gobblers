#include <stdio.h>

#include "board.h"
#include "display.h"
#include "turn.h"
#include "input.h"

int main()
{
	board game = new_game();

	clear_screen();
	
	char player1_name[NAME_MAX_LENGTH];
	char player2_name[NAME_MAX_LENGTH];
	
	input_players_names(player1_name, player2_name);
	delete_carriage_return(player1_name);
	delete_carriage_return(player2_name);
	
	int play_again = 1;
	
	while(play_again)
	{
		turn(game, player1_name, player2_name);
		play_again = declare_winner(&game, player1_name, player2_name);
	}
	
	destroy_game(game);
	return 0;
}

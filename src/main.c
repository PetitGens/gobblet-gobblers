#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/board.h"
#include "../headers/gameloop.h"
#include "../headers/menu.h"
#include "../headers/rating.h"
#include "../headers/display.h"
#include "../headers/bot.h"

int main()
{
	srand(time(NULL));

	//main_menu();

	board game = new_game();
	/*for (int i = 0; i < 10; i++)
		printf("%d\n", random_games(game, PLAYER_1));*/

	place_piece(game, 2, 1, 2);
	place_piece(game, 2, 1, 0);
	place_piece(game, 3, 0, 0);
	place_piece(game, 2, 2, 1);
	place_piece(game, 1, 2, 0);
	place_piece(game, 1, 1, 1);
	move_piece(game, 1, 2, 1, 1);
	place_piece(game, 3, 2, 0);
	place_piece(game, 3, 2, 1);
	place_piece(game, 3, 2, 2);
	move_piece(game, 1, 1, 0, 1);
	move_piece(game, 2, 0, 0, 1);
	move_piece(game, 2, 1, 1, 1);
	place_piece(game, 1, 0, 2);
	place_piece(game, 2, 1, 2);
	move_piece(game, 0, 1, 0, 2);

	enum action_e action;
	int input1[2], input2[2];

	random_action(game, next_player(game), &action, input1, input2);

	print_board(game);
	
	return 0;
}

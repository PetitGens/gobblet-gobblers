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

	// TEST

	board game = new_game();

	place_piece(game, LARGE, 0, 0);
	place_piece(game, LARGE, 0, 1);
	place_piece(game, LARGE, 0, 2);
	place_piece(game, LARGE, 1, 1);
	place_piece(game, LARGE, 1, 0);
	place_piece(game, LARGE, 1, 2);
	place_piece(game, LARGE, 1, 3);
	place_piece(game, LARGE, 2, 0);
	place_piece(game, LARGE, 2, 1);
	place_piece(game, LARGE, 2, 2);
	print_board(game);

	int places[8][3];

	int taille = winnable_places(game, 1, places);

	for (int i = 0; i < taille; i++)
	{
		printf("%d:%d ; %d\n", places[i][0], places[i][1], places[i][2]);
	}

	return 0;
}

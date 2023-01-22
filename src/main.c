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

	printf("%d\n", two_aligned_in_line(game, 0, PLAYER_1));
	printf("%d\n", two_aligned_in_line(game, 1, PLAYER_1));
	printf("%d\n", two_aligned_in_line(game, 2, PLAYER_1));

	printf("%d\n", two_aligned_in_column(game, 0, PLAYER_1));
	printf("%d\n", two_aligned_in_column(game, 1, PLAYER_1));
	printf("%d\n", two_aligned_in_column(game, 2, PLAYER_1));

	int col, line;
	printf("%d", two_aligned_in_diagonal(game, -1, PLAYER_1, &col, &line));
	printf(" ; %d:%d\n", col, line);
	printf("%d", two_aligned_in_diagonal(game, 1, PLAYER_1, &col, &line));
	printf(" ; %d:%d\n", col, line);

	return 0;
}

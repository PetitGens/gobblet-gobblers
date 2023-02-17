#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <SDL2/SDL.h>

#ifdef _WIN64
#include <fcntl.h>
#include <io.h>
#endif

#include "../headers/board.h"
#include "../headers/gameloop.h"
#include "../headers/menu.h"
#include "../headers/rating.h"
#include "../headers/display.h"
#include "../headers/bot.h"

int main()
{
	#ifndef DEBUG
	srand((unsigned int)time(NULL));
	#endif

	#ifdef _WIN64
	_setmode(_fileno(stdout), _O_U16TEXT);
	#endif

	main_menu();

	/*board game = new_game();
	
	movement_s my_move;

	_printf("%d\n", minimax(game, next_player(game), 0, &my_move, 100000));

	if (my_move.action == PLACE)
	{
		place_piece(game, my_move.input1[0], my_move.input2[0], my_move.input2[1]);
	}
	else
	{
		move_piece(game, my_move.input1[0], my_move.input1[1], my_move.input2[0], my_move.input2[1]);
	}

	print_board(game);*/
	
	return 0;
}

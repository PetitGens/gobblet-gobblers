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
	for (int i = 0; i < 10; i++)
		printf("%d\n", random_games(game, PLAYER_1));
		
	
	return 0;
}

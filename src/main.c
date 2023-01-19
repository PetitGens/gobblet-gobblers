#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/board.h"
#include "../headers/gameloop.h"
#include "../headers/menu.h"

int main()
{
	srand(time(NULL));
	main_menu();
	return 0;
}

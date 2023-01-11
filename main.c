#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "gameloop.h"
#include "menu.h"

int main()
{
	srand(time(NULL));
	main_menu();
	return 0;
}

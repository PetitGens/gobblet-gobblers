gobblet : bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o
	gcc -Wall -o gobblet.out bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o -lm -g

bin/main.o : src/main.c
	gcc -Wall -c src/main.c -o bin/main.o -g

bin/board.o : src/board.c
	gcc -Wall -c src/board.c -o bin/board.o -g

bin/display.o : src/display.c
	gcc -Wall -c src/display.c -o bin/display.o -g

bin/turn.o : src/turn.c
	gcc -Wall -c src/turn.c -o bin/turn.o -g

bin/input.o : src/input.c
	gcc -Wall -c src/input.c -o bin/input.o -g

bin/gameloop.o : src/gameloop.c
	gcc -Wall -c src/gameloop.c -o bin/gameloop.o -g

bin/menu.o : src/menu.c
	gcc -Wall -c src/menu.c -o bin/menu.o -g

bin/rating.o : src/rating.c
	gcc -Wall -c src/rating.c -o bin/rating.o -g

bin/bot.o : src/bot.c
	gcc -Wall -c src/bot.c -o bin/bot.o -g
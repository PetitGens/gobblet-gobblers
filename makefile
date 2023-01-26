
gobblet : bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o
	gcc -Wall -Werror -Wconversion -o gobblet.out bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o -lm -g -O3 -DDEBUG

bin/main.o : src/main.c
	mkdir -p bin
	gcc -Wall -Werror -Wconversion -c src/main.c -o bin/main.o -g -DDEBUG

bin/board.o : src/board.c
	gcc -Wall -Werror -Wconversion -c src/board.c -o bin/board.o -g -DDEBUG

bin/display.o : src/display.c
	gcc -Wall -Werror -Wconversion -c src/display.c -o bin/display.o -g -DDEBUG

bin/turn.o : src/turn.c
	gcc -Wall -Werror -Wconversion -c src/turn.c -o bin/turn.o -g -DDEBUG

bin/input.o : src/input.c
	gcc -Wall -Werror -Wconversion -c src/input.c -o bin/input.o -g -DDEBUG

bin/gameloop.o : src/gameloop.c
	gcc -Wall -Werror -Wconversion -c src/gameloop.c -o bin/gameloop.o -g -DDEBUG

bin/menu.o : src/menu.c
	gcc -Wall -Werror -Wconversion -c src/menu.c -o bin/menu.o -g -DDEBUG

bin/rating.o : src/rating.c
	gcc -Wall -Werror -Wconversion -c src/rating.c -o bin/rating.o -g -DDEBUG

bin/bot.o : src/bot.c
	gcc -Wall -Werror -Wconversion -c src/bot.c -o bin/bot.o -g -DDEBUG
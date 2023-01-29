
gobblet : bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o
	gcc -Wall -Werror -Wconversion -o gobblet bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o -lm -O3 -DNDEBUG

bin/main.o : src/main.c
	mkdir -p bin
	gcc -Wall -Werror -Wconversion -c src/main.c -o bin/main.o -DNDEBUG

bin/board.o : src/board.c
	gcc -Wall -Werror -Wconversion -c src/board.c -o bin/board.o -DNDEBUG

bin/display.o : src/display.c
	gcc -Wall -Werror -Wconversion -c src/display.c -o bin/display.o -DNDEBUG

bin/turn.o : src/turn.c
	gcc -Wall -Werror -Wconversion -c src/turn.c -o bin/turn.o -DNDEBUG

bin/input.o : src/input.c
	gcc -Wall -Werror -Wconversion -c src/input.c -o bin/input.o -DNDEBUG

bin/gameloop.o : src/gameloop.c
	gcc -Wall -Werror -Wconversion -c src/gameloop.c -o bin/gameloop.o -DNDEBUG

bin/menu.o : src/menu.c
	gcc -Wall -Werror -Wconversion -c src/menu.c -o bin/menu.o -DNDEBUG

bin/rating.o : src/rating.c
	gcc -Wall -Werror -Wconversion -c src/rating.c -o bin/rating.o -DNDEBUG

bin/bot.o : src/bot.c
	gcc -Wall -Werror -Wconversion -c src/bot.c -o bin/bot.o -DNDEBUG
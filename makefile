#cc = gcc
WARN = -Wall -Werror -Wconversion
OPTI = -O3
#SDL = -lSDL2 -I/usr/include/SDL2

ifeq ($(debug), true)
DEBUGGING = -DDEBUG -g
else
DEBUGGING = -DNDEBUG
endif

gobblet : bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o
	cc $(WARN) -o gobblet bin/main.o bin/board.o bin/display.o bin/turn.o bin/input.o bin/gameloop.o bin/menu.o bin/rating.o bin/bot.o $(SDL) -lm $(OPTI) $(DEBUGGING)

bin/main.o : src/main.c
	mkdir -p bin
	cc $(WARN) -c src/main.c -o bin/main.o $(DEBUGGING) $(OPTI)

bin/board.o : src/board.c
	cc $(WARN) -c src/board.c -o bin/board.o $(DEBUGGING) $(OPTI)

bin/display.o : src/display.c
	cc $(WARN) -c src/display.c -o bin/display.o $(DEBUGGING) $(OPTI)

bin/turn.o : src/turn.c
	cc $(WARN) -c src/turn.c -o bin/turn.o $(DEBUGGING) $(OPTI)

bin/input.o : src/input.c
	cc $(WARN) -c src/input.c -o bin/input.o $(DEBUGGING) $(OPTI)

bin/gameloop.o : src/gameloop.c
	cc $(WARN) -c src/gameloop.c -o bin/gameloop.o $(DEBUGGING) $(OPTI)

bin/menu.o : src/menu.c
	cc $(WARN) -c src/menu.c -o bin/menu.o $(DEBUGGING) $(OPTI)

bin/rating.o : src/rating.c
	cc $(WARN) -c src/rating.c -o bin/rating.o $(DEBUGGING) $(OPTI)

bin/bot.o : src/bot.c
	cc $(WARN) -c src/bot.c -o bin/bot.o $(DEBUGGING) $(OPTI)

clean :
	rm bin/*
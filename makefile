gobblet : main.o display.o turn.o input.o gameloop.o menu.o rating.o
	gcc -Wall -o gobblet main.o board.o display.o turn.o input.o gameloop.o menu.o rating.o

main.o : main.c
	gcc -Wall -c main.c

board.o : board.c
	gcc -Wall -c board.c

display.o : display.c
	gcc -Wall -c display.c

turn.o : turn.c
	gcc -Wall -c turn.c

input.o : input.c
	gcc -Wall -c input.c

gameloop.o : gameloop.c
	gcc -Wall -c gameloop.c

menu.o : menu.c
	gcc -Wall -c menu.c

rating.o : rating.c
	gcc -Wall -c rating.c
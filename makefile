gobblet : main.o display.o turn.o input.o
	gcc -Wall -o gobblet main.o board.o display.o turn.o input.o

main.o : main.c
	gcc -Wall -c main.c

display.o : display.c
	gcc -Wall -c display.c

turn.o : turn.c
	gcc -Wall -c turn.c

input.o : input.c
	gcc -Wall -c input.c
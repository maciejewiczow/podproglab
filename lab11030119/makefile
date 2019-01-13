CC= gcc
CFLAGS= -Wall -Wextra -g
LIB= -lm

FILES= main.c board.c arguments.c
OUT= gameOfLife.out

run: lifegame
	gnome-terminal --profile holdopen -- ./$(OUT) boards/test.txt
	wmctrl -a 'Terminal'

lifegame:
	$(CC) $(CFLAGS) $(FILES) -o $(OUT) $(LIB)

clean:
	rm $(OUT)

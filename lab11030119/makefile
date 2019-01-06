CC= gcc
CFLAGS= -Wall -Wextra
LIB= -lm

FILES= main.c board.c
OUT= gameOfLife.out

buildAndRun:
	$(CC) $(CFLAGS) $(FILES) -o $(OUT) $(LIB)
	gnome-terminal --profile holdopen -- ./$(OUT)
	wmctrl -a 'Terminal'

clean:
	rm $(OUT)

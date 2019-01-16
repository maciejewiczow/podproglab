CC= gcc
CFLAGS= -Wall -Wextra -g
LIB= -lm

FILES= main.c board.c arguments.c
OUT= gameOfLife.out

all: lifegame

run: lifegame
	gnome-terminal --profile holdopen -- ./bin/$(OUT) boards/test.txt
	wmctrl -a 'Terminal'

lifegame:
	mkdir -p bin
	cd ./src && \
	$(CC) $(CFLAGS) $(FILES) -o ../bin/$(OUT) $(LIB)

clean:
	rm bin/*

#!/bin/bash

pathNoExt=$(echo "$1" | cut -f 1 -d '.')

if [ -f "$2/makefile" ]; then

cd $2
make run

elif [ -f "makefile" ]; then

make run

else

gcc -Wall -Wextra "$pathNoExt.c" -o "$pathNoExt.out" -lm -g

if [ $? -eq 0 ]; then
    gnome-terminal --profile holdopen -- ./"$pathNoExt.out"
	wmctrl -a 'Terminal'
fi
fi

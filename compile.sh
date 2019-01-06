#!/bin/bash

pathNoExt=$(echo "$1" | cut -f 1 -d '.')

if [ -f "$2/makefile" ]; then

cd $2
make buildAndRun

else

gcc -Wall -Wextra "$pathNoExt.c" -o "$pathNoExt.out" -lm

if [ $? -eq 0 ]; then
 "$pathNoExt.out"
fi
fi

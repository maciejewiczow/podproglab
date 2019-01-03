#!/bin/bash

pathNoExt=$(echo "$1" | cut -f 1 -d '.')

gcc -Wall -Wextra "$pathNoExt.c" -o "$pathNoExt.out" -lm

if [ $? -eq 0 ]; then
 "$pathNoExt.out"
fi

#!/bin/bash

pathNoExt=$(echo "$1" | cut -f 1 -d '.')

gcc -Wall -Wextra "$pathNoExt.c" -o "$pathNoExt.out" -lm
"$pathNoExt.out"

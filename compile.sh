#!/bin/bash

gcc -Wall -Wextra "$1/$2.c" -o "$1/$2.out" -lm
"$1/$2.out"
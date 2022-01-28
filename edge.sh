#!/bin/sh

CC="gcc"
FLAGS="-W -Wall -ansi -pedantic -O3"
INCLUDE="include"

RM="rm -rf"

H="src/util.c src/lexer.c src/memory.c src/token.c"

mkdir -p out
$CC $FLAGS -I$INCLUDE $H src/main.c -o out/main.o
./out/main.o
$RM out/*.o
rmdir out
#!bin/bash

COMP=g++
SRC=" main.cpp glad.c oglhelper.cpp "
LINK=" -lglfw "
OUT="-omain"

$COMP $SRC $LINK $OUT
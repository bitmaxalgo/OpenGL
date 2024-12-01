#!bin/bash

GCX=g++
SRC="main.cpp text.cpp oglhelper.cpp glad.c"
LFLAGS=" -lglfw "

$GCX $SRC $LFLAGS -o"main"
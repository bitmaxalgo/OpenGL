#!/bin/bash

SRC=" src/main.cpp src/glad.c src/oglhelper.cpp src/text.cpp"

CXX=g++
LIBS="-lglfw"

[ ! -d "build" ] && mkdir build

$CXX $SRC $LIBS -o build/"main" 


GXX=g++
SRC=" src/main.cpp "
LIB=" -lglfw "
OUT="-o main"

if [ -L "./Build" ]
then
    echo "Build directory not found. Creating directory."
    mkdir ./build
    echo "Build directory created."
else
    echo "Build directory already exists. Using directory."
fi

$GXX $SRC $LIB $OUT
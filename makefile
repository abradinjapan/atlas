all:
	g++ ./source/main.cpp -Wextra -Wall -o ../atlas.elf -g -lSDL3 -lGL -lGLEW -lm

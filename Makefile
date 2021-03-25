CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror  `pkg-config sdl2 --cflags`
LIBS = `pkg-config sdl2--libs`-lm `pkg-config SDL2_image --libs`
OBJ = dr4

all install: main.c
	$(CC) $(CFLAGS) main.c $(LIBS) -o $(OBJ)

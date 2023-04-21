CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: src/main.o src/state.o src/Scenes/Jogo/desenhaJogo.o src/Scenes/Jogo/eventosJogo.o src/Scenes/MenuInicial/desenhaMenuInicial.o src/Scenes/MenuInicial/eventosMenuInicial.o
# Compile main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
# Delete recursively all objects (.o) files
	find . -type f -name '*.o' -delete

dev:
# Clean, compile and run 
	make clean && make && make clean && ./jogo

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

OBJ = src/main.o \
			src/state.o \
			src/Scenes/MenuInicial/desenhaMenuInicial.o src/Scenes/MenuInicial/eventosMenuInicial.o \
			src/Scenes/SelecionarJogador/desenhaSelecionarJogador.o src/Scenes/SelecionarJogador/eventosSelecionarJogador.o \
			src/Scenes/Jogo/desenhaJogo.o src/Scenes/Jogo/eventosJogo.o \
			src/Scenes/Controlos/desenhaControlos.o src/Scenes/Controlos/eventosControlos.o \
			src/Scenes/Sobre/desenhaSobre.o src/Scenes/Sobre/eventosSobre.o \
			src/Scenes/Sair/desenhaSair.o src/Scenes/Sair/eventosSair.o

jogo: $(OBJ)
# Compile main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
# Delete recursively all objects (.o) files
	find . -type f -name '*.o' -delete

dev:
# Clean, compile and run 
	make clean && make && make clean && ./jogo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

void gerar(State *state) {
	state->jogoAtual.jogador.posicao.x = 10;
	state->jogoAtual.jogador.posicao.y = 10;
}

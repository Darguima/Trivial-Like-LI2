#include <ncurses.h>

#include "../../state.h"
#include "../Jogo/desenhaJogo.h"

void eventosMenuInicial(State *state) {
	int key = getch();

	switch(key) {
		case 'j': 
		gerarMapa (state->mapa.width,state->mapa.height,state->mapa.matrix);
			state->sceneAtual = SelecionarJogador; break;
		
		case 'c': 
			state->sceneAtual = Controlos; break;

		case 's': 
			state->sceneAtual = Sobre; break;

		case 'q':
			state->sceneAtual = Sair; break;
	}
}
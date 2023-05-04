#include <ncurses.h>

#include "../../state.h"
#include "../Jogo/geraMapa.h"

void eventosMenuInicial(State *state) {
	int key = getch();

	switch(key) {
		case 'j': 
		geraMapa(state->mapa.width,state->mapa.height,state->mapa.matrix);
		state->jogoAtual.jogador.posicao.x=5;
		state->jogoAtual.jogador.posicao.y=5;
			state->sceneAtual = SelecionarJogador; break;
		
		case 'c': 
			state->sceneAtual = Controlos; break;

		case 's': 
			state->sceneAtual = Sobre; break;

		case 'q':
			state->sceneAtual = Sair; break;
	}
}
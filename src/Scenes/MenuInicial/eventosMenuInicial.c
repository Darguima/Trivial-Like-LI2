#include <ncurses.h>

#include "../../state.h"

void eventosMenuInicial(State *state) {
	int key = getch();

	switch(key) {
		case 'j': 
			state->sceneAtual = SelecionarJogador; break;
		
		case 'c': 
			state->sceneAtual = Controlos; break;

		case 's': 
			state->sceneAtual = Sobre; break;

		case 'q':
			state->sceneAtual = Sair; break;
	}
}
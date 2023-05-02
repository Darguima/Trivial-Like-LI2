#include <ncurses.h>

#include "../../state.h"

void eventosMenuInicial(State *state) {
	int key = getch();

	switch(key) {
		case '1': 
			state->sceneAtual = SelecionarJogador; break;
		
		case '2': 
			state->sceneAtual = Controlos; break;

		case '3': 
			state->sceneAtual = Sobre; break;

		case '4':
			state->sceneAtual = Sair; break;
	}
}
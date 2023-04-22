#include <ncurses.h>

#include "../../state.h"

void eventosSelecionarJogador(State *state) {
	int key = getch();

	switch(key) {
		case 'j': 
			state->sceneAtual = Jogo;
			break;
			
		case 'q':
			state->sceneAtual = MenuInicial;
			break;
	}
}
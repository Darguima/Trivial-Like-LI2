#include <stdlib.h>
#include <ncurses.h>

#include "../../state.h"

void eventosMenuInicial(State *state) {
	int key = getch();

	switch(key) {
		case 'j': 
			state->sceneAtual = Jogo; break;
			
		case 'q': endwin(); exit(0); break;
	}
}
#include <ncurses.h>

#include "../../state.h"


void eventosControlos(State *state) {
	int key = getch();

	switch(key) {
		case 'q':
			state->sceneAtual = MenuInicial;
			break;
	}
}
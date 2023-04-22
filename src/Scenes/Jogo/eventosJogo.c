#include <ncurses.h>

#include "../../state.h"

void mover_jogador(State *state, int dx, int dy) {
	state->jogoAtual.jogador.posicao.x += dx;
	state->jogoAtual.jogador.posicao.y += dy;
}

void eventosJogo(State *state) {
	int key = getch();

	switch(key) {
		case KEY_A1:
		case '7': 
			mover_jogador(state, -1, -1);
			break;
			
		case KEY_UP:
		case '8': 
			mover_jogador(state, -1, +0);
			break;
			
		case KEY_A3:
		case '9': 
			mover_jogador(state, -1, +1);
			break;
			
		case KEY_LEFT:
		case '4': 
			mover_jogador(state, +0, -1);
			break;
			
		case KEY_RIGHT:
		case '6': 
			mover_jogador(state, +0, +1);
			break;
			
		case KEY_C1:
		case '1': 
			mover_jogador(state, +1, -1);
			break;
			
		case KEY_DOWN:
		case '2': 
			mover_jogador(state, +1, +0);
			break;
			
		case KEY_C3:
		case '3': 
			mover_jogador(state, +1, +1);
			break;
			
		case 'q':
			state->sceneAtual = MenuInicial;
			break;
	}
}
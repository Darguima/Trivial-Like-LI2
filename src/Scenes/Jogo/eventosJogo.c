#include <ncurses.h>
#include <json-c/json.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"

void mover_jogador(State *state, int dx, int dy)
{
	state->jogoAtual.jogador.posicao.x += dx;
	state->jogoAtual.jogador.posicao.y += dy;
}


void eventosJogo(State *state)
{
	char file[10]; 
	int key = getch();

	switch (key)
	{
	case 's':
		
		sprintf(file, "%d.json", state->jogoAtual.jogador.numSave);
		save_game_state(file, state->jogoAtual.jogador.vida, state->jogoAtual.jogador.username, state->jogoAtual.jogador.numMapaAtual, state->jogoAtual.jogador.dinheiro, state->jogoAtual.jogador.armaPrincipal.index, state->jogoAtual.jogador.armaSecundaria.index);

		break;
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
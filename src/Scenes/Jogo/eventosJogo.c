#include <ncurses.h>

#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"
#include "./atualizarAposMovimento.h"

void mover_jogador(State *state, int dx, int dy)
{
	int temp_x = state->jogoAtual.jogador.posicao.x + dx;
	int temp_y = state->jogoAtual.jogador.posicao.y + dy;

	if (is_pos_free(state->mapa, temp_x, temp_y))
	{
		state->jogoAtual.jogador.posicao.x = temp_x;
		state->jogoAtual.jogador.posicao.y = temp_y;
	}

	atualizarAposMovimento(state);
}

void eventosJogo(State *state)
{
	int key = getch();

	ArmaNoMapa *armaSobreposta;

	switch (key)
	{
	/* Interação com mapa */
	case 'p':
		if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->available) {
			state->jogoAtual.jogador.armaPrincipal = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->available = 0;
		}
		break;

	/* Setas */
	case KEY_A1:
	case '7':
		mover_jogador(state, -1, -1);
		break;

	case KEY_UP:
	case '8':
		mover_jogador(state, 0, -1);
		break;

	case KEY_A3:
	case '9':
		mover_jogador(state, +1, -1);
		break;

	case KEY_LEFT:
	case '4':
		mover_jogador(state, -1, 0);
		break;

	case KEY_RIGHT:
	case '6':
		mover_jogador(state, +1, 0);
		break;

	case KEY_C1:
	case '1':
		mover_jogador(state, -1, +1);
		break;

	case KEY_DOWN:
	case '2':
		mover_jogador(state, 0, +1);
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
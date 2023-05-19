#include <stdlib.h>
#include <ncurses.h>

#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"

#define UNUSED(x) (void)(x)

void eventosGameOver(State *state)
{
	UNUSED(state);

	int key = getch();
	int new_dinheiro;

	switch (key)
	{
	case 'r':
		new_dinheiro = state->jogoAtual.jogador.dinheiro - 40 * state->jogoAtual.jogador.quantidadeMortes;
		if (new_dinheiro >= 0)
		{
			state->jogoAtual.jogador.dinheiro = new_dinheiro;
			state->sceneAtual = Jogo;
			save_game_state(state);
		}
		break;

	case 'm':
		state->sceneAtual = MenuInicial;
		break;

	case 'q':
		endwin();
		exit(0);
		break;
	}
}
#include <ncurses.h>

#include "../../state.h"

void eventosDefinicoes(State *state)
{
	int key = getch();

	switch (key)
	{
	case 'q':
		state->sceneAtual = MenuInicial;
		break;

	case '1':
		state->scenesVariables.definicoesSceneVars.ask_matrix_size = 1;
		break;

	case '2':
		if (++state->jogoAtual.dificuldade == DIFICIL + 1)
			state->jogoAtual.dificuldade = FACIL;
		break;

	case '3':
		state->jogoAtual.mapa_desconhecido_ativo = 1 - state->jogoAtual.mapa_desconhecido_ativo;
		if (state->jogoAtual.mapa_desconhecido_ativo)
			state->jogoAtual.iluminacao_ativa = 1;
		break;

	case '4':
		if (!state->jogoAtual.mapa_desconhecido_ativo)
			state->jogoAtual.iluminacao_ativa = 1 - state->jogoAtual.iluminacao_ativa;
		break;
	}
}
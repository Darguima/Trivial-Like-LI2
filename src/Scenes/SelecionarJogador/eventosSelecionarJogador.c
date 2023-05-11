#include <ncurses.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"

void eventosSelecionarJogador(State *state)
{
	int key = getch();

	switch (key)
	{
	case '1':
		state->jogoAtual.jogador.numSave = 1;
		load_game_state("1.json", state);
		state->sceneAtual = Jogo;
		break;

	case '2':
		state->jogoAtual.jogador.numSave = 2;
		load_game_state("2.json", state);
		state->sceneAtual = Jogo;
		break;

	case '3':
		state->jogoAtual.jogador.numSave = 3;
		load_game_state("3.json", state);
		state->sceneAtual = Jogo;
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}

#include <ncurses.h>
#include <json-c/json.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"



void eventosSelecionarJogador(State *state)
{

	int key = getch();

	switch (key)
	{
	case '1':
		// jogador
		state->jogoAtual.jogador.numSave = 1;
		// load ficheiro 1
		load_game_state("1.json", state);
		// começar jogo
		state->sceneAtual = Jogo;
		break;
	case '2':
		// jogador
		state->jogoAtual.jogador.numSave = 2;
		// load ficheiro 2
		load_game_state("2.json", state);
		// começar jogo
		state->sceneAtual = Jogo;
		break;
	case '3':
		// jogador
		state->jogoAtual.jogador.numSave = 3;
		// load ficheiro 3
		load_game_state("3.json", state);
		// começar jogo
		state->sceneAtual = Jogo;
		break;

	case Jogo:
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}

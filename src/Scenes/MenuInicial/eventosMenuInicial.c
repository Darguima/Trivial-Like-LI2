#include <ncurses.h>

#include "../../state.h"

void eventosMenuInicial(State *state)
{
	int key = getch();

	switch (key)
	{
	case 'j':
	case '1':
		state->sceneAtual = SelecionarJogador;
		break;

	case '2':
		state->sceneAtual = Definicoes;
		break;

	case '3':
		state->sceneAtual = Controlos;
		break;

	case '4':
		state->sceneAtual = Sobre;
		break;

	case 'q':
	case '5':
		state->sceneAtual = Sair;
		break;
	}
}
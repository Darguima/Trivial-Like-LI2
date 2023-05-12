#include <ncurses.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"

void eventosSelecionarJogador(State *state)
{
	int key = getch();

	switch (key)
	{
	case '1':
		if (state->jogoAtual.jogador.delete == 1)
		{
			if (remove("1.json") != 0)
			{
				state->jogoAtual.jogador.faildelete = 1;
			}
			state->jogoAtual.jogador.delete = 0;
		}
		else
		{
			state->jogoAtual.jogador.numSave = 1;
			load_game_state("1.json", state);
		}
		break;

	case '2':
		if (state->jogoAtual.jogador.delete == 1)
		{
			if (remove("2.json") != 0)
			{
				state->jogoAtual.jogador.faildelete = 1;
			}
			state->jogoAtual.jogador.delete = 0;
		}
		else
		{

			state->jogoAtual.jogador.numSave = 2;
			load_game_state("2.json", state);
		}
		break;

	case '3':
		if (state->jogoAtual.jogador.delete == 1)
		{
			if (remove("3.json") != 0)
			{
				state->jogoAtual.jogador.faildelete = 1;
			}
			state->jogoAtual.jogador.delete = 0;
		}
		else
		{

			state->jogoAtual.jogador.numSave = 3;
			load_game_state("3.json", state);
		}
		break;
	case 'j':
		if (state->jogoAtual.jogador.askUser == 2)
		{
			state->jogoAtual.jogador.askUser = 0;
			state->sceneAtual = Jogo;
		}
		break;
	case 'd':
		state->jogoAtual.jogador.delete = 1;
		break;
	case 'a':
		state->jogoAtual.jogador.faildelete = 0;
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}

#include <ncurses.h>
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"

void eventosSelecionarJogador(State *state)
{
	int key = getch();

	switch (key)
	{
	case '1':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("1.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else
		{
			if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
			{
				state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
				state->jogoAtual.jogador.numSave = 1;
				load_game_state("1.json", state);
				if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0)
				{
					state->sceneAtual = Jogo;
				}
			}
		}
		break;

	case '2':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("2.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else
		{
			if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
			{
				state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
				state->jogoAtual.jogador.numSave = 2;
				load_game_state("2.json", state);
				if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0)
				{
					state->sceneAtual = Jogo;
				}
			}
		}
		break;

	case '3':
		if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
		{
			if (remove("3.json") != 0)
			{
				state->scenesVariables.selecionarJogadorSceneVars.faildelete = 1;
			}
			state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		}
		else
		{

			if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0 || state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
			{
				state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
				state->jogoAtual.jogador.numSave = 3;
				load_game_state("3.json", state);
				if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 0)
				{
					state->sceneAtual = Jogo;
				}
			}
		}
		break;
	case 'j':
		if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 2)
		{
			state->scenesVariables.selecionarJogadorSceneVars.askUser = 0;
			state->sceneAtual = Jogo;
		}
		break;
	case 'd':
		state->scenesVariables.selecionarJogadorSceneVars.faildelete = 0;
		state->scenesVariables.selecionarJogadorSceneVars.delete = 1;
		break;
	case 'a':
		state->scenesVariables.selecionarJogadorSceneVars.faildelete = 0;
		state->scenesVariables.selecionarJogadorSceneVars.delete = 0;
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}

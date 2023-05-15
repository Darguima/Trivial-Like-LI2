#include <ncurses.h>
#include <stdlib.h>
#include "./atualizarAposMovimento.h"
#include "../../state.h"
#include "../../SalvarJogo/salvarJogo.h"
#include "../../MapaUtils/mapaUtils.h"

void mover_jogador(State *state, int dx, int dy)
{
	int temp_x = state->jogoAtual.jogador.posicao.x + dx;
	int temp_y = state->jogoAtual.jogador.posicao.y + dy;

	if (estaSemParede(state->mapa, temp_x, temp_y))
	{
		state->jogoAtual.jogador.posicao.x = temp_x;
		state->jogoAtual.jogador.posicao.y = temp_y;
	}

	atualizarAposMovimento(state);
}

/*
Arma:
	1 - para principal
	2 - para secundária
*/
void danoComProbabilidadeAcertar(State *state, int arma, MobNoMapa *mob_sobreposto)
{
	Arma arma_player = arma == 1 ? state->jogoAtual.jogador.armaPrincipal : state->jogoAtual.jogador.armaSecundaria;
	Arma arma_mob = mob_sobreposto->mob.arma;

	int player_acertou = rand() % 100 < arma_player.probabilidade ? 1 : 0;
	int mob_acertou = rand() % 100  < arma_mob.probabilidade ? 1 : 0;

	mob_sobreposto->mob.vida -= arma_player.dano * player_acertou;
	state->jogoAtual.jogador.vida -= arma_mob.dano * mob_acertou;
}

// a função reageVida verifica se o jogador tá morto para dar GameOver
void reageVida(State *state)
{
	if (state->jogoAtual.jogador.vida <= 0)
	{
		// Se a vida ficar a 0, o jogo acaba
		state->sceneAtual = GameOver;
		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
	}
}

void eventosJogo(State *state)
{
	int key = getch();
	char file[10];

	ArmaNoMapa *armaSobreposta;
	ObjetoNoMapa *objetoSobreposto;
	MobNoMapa *mob_sobreposto;

	switch (key)
	{
	case 's':

		sprintf(file, "%d.json", state->jogoAtual.jogador.numSave);
		save_game_state(file, state->jogoAtual.jogador.vida, state->jogoAtual.jogador.username, state->jogoAtual.jogador.numMapaAtual, state->jogoAtual.jogador.dinheiro, state->jogoAtual.jogador.armaPrincipal.index, state->jogoAtual.jogador.armaSecundaria.index);
		break;

	/* Interação com mapa */
	case 'z':
		// atacar com principal
		if (esta_sobre_mob(state, &mob_sobreposto))
		{
			danoComProbabilidadeAcertar(state, 1, mob_sobreposto);
			reageVida(state); // verifica se o jogador tem vida 0
		}

		// Pegar arma principal
		else if (esta_sobre_arma(state, &armaSobreposta))
		{
			state->jogoAtual.jogador.armaPrincipal = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
		}

		break;

	case 'x':
		// Atacar com secundária
		if (esta_sobre_mob(state, &mob_sobreposto))
		{
			danoComProbabilidadeAcertar(state, 2, mob_sobreposto);
			reageVida(state); // verifica se o jogador tem vida 0
		}

		// Pegar arma secundária
		else if (esta_sobre_arma(state, &armaSobreposta))
		{
			state->jogoAtual.jogador.armaSecundaria = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
		}

		break;

	case 'e':
		// Pegar um objeto
		if (esta_sobre_objeto(state, &objetoSobreposto))
		{
			objetoSobreposto->disponivel = 0;
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
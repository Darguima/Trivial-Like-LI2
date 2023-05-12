#include <ncurses.h>
#include <unistd.h>
#include "./atualizarAposMovimento.h"
#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"
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

	ArmaNoMapa *armaSobreposta;
	MobNoMapa *mob_sobreposto;

	switch (key)
	{
		/* Interação com mapa */

	case 'z':
		// atacar com principal
		if (esta_sobre_mob(state, &mob_sobreposto) && mob_sobreposto->mob.vida > 0)
		{
			int dano = state->jogoAtual.jogador.armaPrincipal.dano;

			mob_sobreposto->mob.vida -= dano;
			state->jogoAtual.jogador.vida -= mob_sobreposto->mob.arma.dano;

			reageVida(state); // verifica se o jogador tem vida 0
		}

		// Pegar arma principal
		else if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
		{
			state->jogoAtual.jogador.armaPrincipal = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
		}

		break;

	case 'x':
		// Atacar com secundária
		if (esta_sobre_mob(state, &mob_sobreposto) && mob_sobreposto->mob.vida > 0)
		{
			int dano = state->jogoAtual.jogador.armaSecundaria.dano;

			mob_sobreposto->mob.vida -= dano;
			state->jogoAtual.jogador.vida -= mob_sobreposto->mob.arma.dano;

			reageVida(state); // verifica se o jogador tem vida 0
		}

		// Pegar arma secundária
		else if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
		{
			state->jogoAtual.jogador.armaSecundaria = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
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
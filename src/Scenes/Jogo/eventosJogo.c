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
	// limpa o menu lateral antes de desenhar novamente
	move(state->mapa.terminal.height - 4, 20);
	clrtoeol();
	move(state->mapa.terminal.height - 2, 20);
	clrtoeol();
	atualizarAposMovimento(state);
}

void eventosJogo(State *state)
{
	int key = getch();

	ArmaNoMapa *armaSobreposta;
	MobNoMapa *mob_sobreposto;

	// Se a vida ficar a 0, o jogo acaba
	if (state->jogoAtual.jogador.vida <= 0)
	{
		state->sceneAtual = GameOver;
		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
	}

	switch (key)
	{
		/* Interação com mapa */

	case 'z':
		// Pegar arma principal
		if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
		{
			state->jogoAtual.jogador.armaPrincipal = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
		}
		// atacar com principal
		if (esta_sobre_mob(state, &mob_sobreposto) && mob_sobreposto->mob.vida > 0)
		{
			int dano = state->jogoAtual.jogador.armaPrincipal.dano;

			mob_sobreposto->mob.vida -= dano;
			state->jogoAtual.jogador.vida -= mob_sobreposto->mob.arma.dano;
		}
		break;

	case 'x':
		// Pegar arma secundária
		if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
		{
			state->jogoAtual.jogador.armaSecundaria = armaSobreposta->arma;
			// Adicionar Arma ao inventário
			armaSobreposta->disponivel = 0;
		}
		// Atacar com secundária
		if (esta_sobre_mob(state, &mob_sobreposto) && mob_sobreposto->mob.vida > 0)
		{
			int dano = state->jogoAtual.jogador.armaSecundaria.dano;

			mob_sobreposto->mob.vida -= dano;
			state->jogoAtual.jogador.vida -= mob_sobreposto->mob.arma.dano;
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
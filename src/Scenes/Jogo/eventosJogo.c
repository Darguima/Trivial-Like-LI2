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

int ataqueComProbabilidade(Arma arma, int *vida_vitima)
{
	int acertou = rand() % 100 < arma.probabilidade ? 1 : 0;

	*vida_vitima -= arma.dano * acertou;

	return acertou;
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
			ataqueComProbabilidade(state->jogoAtual.jogador.armaPrincipal, &(mob_sobreposto->mob.vida));
			ataqueComProbabilidade(mob_sobreposto->mob.arma, &(state->jogoAtual.jogador.vida));
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
			ataqueComProbabilidade(state->jogoAtual.jogador.armaSecundaria, &(mob_sobreposto->mob.vida));
			ataqueComProbabilidade(mob_sobreposto->mob.arma, &(state->jogoAtual.jogador.vida));
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
			objetoSobreposto->objeto.quantidade++;
		}
		break;

		/* Setas */
	case KEY_UP:
		mover_jogador(state, 0, -1);
		break;

	case KEY_LEFT:
		mover_jogador(state, -1, 0);
		break;

	case KEY_RIGHT:
		mover_jogador(state, +1, 0);
		break;

	case KEY_DOWN:
		mover_jogador(state, 0, +1);
		break;

		/* inventário */
	case '1':
		state->jogoAtual.mensagem_inventario = pocaoVidaP.mensagem;
		if (state->jogoAtual.jogador.vida < state->jogoAtual.jogador.vidaMaxima - 40)
		{
			state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vida + 40;
		}
		else
		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
		break;
	
	case '2':
		state->jogoAtual.mensagem_inventario = pocaoVidaG.mensagem;
		state->jogoAtual.mensagem_inventario = pocaoVidaG.mensagem;
		if (state->jogoAtual.jogador.vida < state->jogoAtual.jogador.vidaMaxima - 70)
		{
			state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vida + 70;
		}
		else
		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
		break;
	
	case '3':
		state->jogoAtual.mensagem_inventario = pocaoVidaD.mensagem;

		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
		break;
	
	case '4':
		state->jogoAtual.mensagem_inventario = pocaoAumentoVida.mensagem;

		if (state->jogoAtual.jogador.vidaMaxima < 275)
		{
			state->jogoAtual.jogador.vidaMaxima = state->jogoAtual.jogador.vidaMaxima + 25;
		}
		else 
		state->jogoAtual.jogador.vidaMaxima = 300;
		break;
	
	case '5':
		state->jogoAtual.mensagem_inventario = pocaoMagica.mensagem;

		if (state->jogoAtual.jogador.vidaMaxima < 285)
		{
			state->jogoAtual.jogador.vidaMaxima = state->jogoAtual.jogador.vidaMaxima + 15;
		}
		else 
		state->jogoAtual.jogador.vidaMaxima = 300;

		state->jogoAtual.jogador.vida = state->jogoAtual.jogador.vidaMaxima;
		break;
	
	case '6':
		state->jogoAtual.mensagem_inventario = portalDeBolso.mensagem;
		break;
	
		/* Sair */
	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}
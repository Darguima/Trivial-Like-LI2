#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaMapa(WINDOW *window, int largura_mapa, int altura_mapa, ElementosDoMapa **mapa)
{
	for (int x = 0; x < largura_mapa; x++)
	{
		for (int y = 0; y < altura_mapa; y++)
		{
			switch (mapa[x][y])
			{
			case Parede:
				mvwaddch(window, y, x, '#');
				break;

			case Moeda:
				wattron(window, COLOR_PAIR(YellowBlack));
				mvwaddch(window, y, x, 'c');
				wattroff(window, COLOR_PAIR(YellowBlack));
				break;

			default:
				mvwaddch(window, y, x, ' ');
				break;
			}
		}
	}
}

void desenhaArmas(WINDOW *window, State *state)
{
	for (int arma = 0; arma < armasNoMapaLength; arma++)
	{
		ArmaNoMapa armaAtual = state->jogoAtual.armas[arma];

		if (!armaAtual.disponivel)
			continue;

		wattron(window, COLOR_PAIR(GreenBlack));
		mvwaddch(window, armaAtual.posicao.y, armaAtual.posicao.x, '%');
		wattroff(window, COLOR_PAIR(GreenBlack));
	}
}

void desenhaMobs(WINDOW *window, State *state)
{
	for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
	{
		MobNoMapa mobAtual = state->jogoAtual.mobs[mob_i];

		if (!(mobAtual.mob.vida > 0))
			continue;

		wattron(window, COLOR_PAIR(BlackRed));
		mvwaddch(window, mobAtual.posicao.y, mobAtual.posicao.x, 'M');
		wattroff(window, COLOR_PAIR(BlackRed));
	}
}

void desenhaJogo(WINDOW *window, State *state, int x, int y, ElementosDoMapa **mapa)
{
	desenhaMapa(window, x, y, mapa);
	desenhaArmas(window, state);
	desenhaMobs(window, state);

	wattron(window, COLOR_PAIR(BlueBlack));
	mvwaddch(window, state->jogoAtual.jogador.posicao.y, state->jogoAtual.jogador.posicao.x, '@');
	wattroff(window, COLOR_PAIR(BlueBlack));

	wmove(window, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	wrefresh(window);

	return;
}

void desenhaMenusLaterais(WINDOW *window, State *state)
{
	UNUSED(window);

	// fronteira menu esquerdo
	WINDOW *l_win = newwin(state->mapa.height, 20, 5, 0);
	box(l_win, 0, 0);
	wrefresh(l_win);

	// fronteira menu direito
	WINDOW *r_win = newwin(state->mapa.height, 20, 5, state->mapa.terminal.width - 20);
	box(r_win, 0, 0);
	wrefresh(r_win);

	// vida
	mvprintw(7, 1, "%s", "VIDA:");
	mvprintw(7, 6, "%d", state->jogoAtual.jogador.vida);
	if (state->jogoAtual.jogador.vida > 96)
	{
		mvprintw(8, 1, "%s", "#################");
	}
	else if (state->jogoAtual.jogador.vida != 0)
	{
		for (int i = 0; i < (state->jogoAtual.jogador.vida / 6) + 1; i++)
		{
			mvprintw(8, 1 + i, "%s", "#");
		}
	}

	// arma principal
	attron(A_BOLD);
	mvprintw(11, 1, "%s", "PRINCIPAL ");
	attroff(A_BOLD);
	mvprintw(11, 12, "[Z]:");
	mvprintw(12, 1, "%s", state->jogoAtual.jogador.armaPrincipal.nome);
	mvprintw(13, 1, "%d pts de dano ", state->jogoAtual.jogador.armaPrincipal.dano);
	mvprintw(14, 1, "%d%% de acertar", state->jogoAtual.jogador.armaPrincipal.probabilidade);

	// arma secundaria
	attron(A_BOLD);
	mvprintw(16, 1, "%s", "SECUNDARIA ");
	attroff(A_BOLD);
	mvprintw(16, 12, "[X]:");
	mvprintw(17, 1, "%s", state->jogoAtual.jogador.armaSecundaria.nome);
	mvprintw(18, 1, "%d pts de dano", state->jogoAtual.jogador.armaSecundaria.dano);
	mvprintw(19, 1, "%d%% de acertar", state->jogoAtual.jogador.armaSecundaria.probabilidade);

	// dinheiro
	attron(A_BOLD);
	mvprintw(21, 1, "%s", "MOEDAS:");
	attroff(A_BOLD);
	mvprintw(21, 9, "%d", state->jogoAtual.jogador.dinheiro);

	// num mapa atual
	mvprintw(3, (state->mapa.terminal.width - 43) / 2 + 7, "%s", "M A P A    A T U A L   :   ");
	mvprintw(3, ((state->mapa.terminal.width - 43) / 2) + 35, "%d", state->jogoAtual.jogador.numMapaAtual);

	// mensagem
	mvprintw(state->mapa.terminal.height - 4, 20, "%s", state->jogoAtual.mensagem_descricao);
	mvprintw(state->mapa.terminal.height - 2, 20, "%s", state->jogoAtual.mensagem_controlos);
}
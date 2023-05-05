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

void desenhaMapa(WINDOW *window, int largura_mapa, int altura_mapa, int **mapa) {
	for (int x = 0; x < largura_mapa; x++)
	{
		for (int y = 0; y < altura_mapa; y++)
		{
			switch (mapa[x][y])
			{
			case Parede:
				mvwaddch(window, y, x, '#');
				break;

			default:
				mvwaddch(window, y, x, ' ');
				break;
			}
		}
	}
}

void desenhaJogo(WINDOW *window, State *state, int x, int y, int **mapa)
{
	desenhaMapa(window, x, y, mapa);

	mvwaddch(window, state->jogoAtual.jogador.posicao.y, state->jogoAtual.jogador.posicao.x, '@');

	wmove(window, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	wrefresh(window);

	return;
}

void desenhaMenusLaterais(WINDOW *window, State *state)
{
	UNUSED(window);

	// fronteira menu esquerdo
	WINDOW *l_win = newwin(state->mapa.height - 10, 20, 5, 0);
	box(l_win, 0, 0);
	wrefresh(l_win);

	// fronteira menu direito
	WINDOW *r_win = newwin(state->mapa.height - 10, 20, 5, state->mapa.width - 20);
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
	mvprintw(10, 1, "%s", "ARMA PRINCIPAL:");
	mvprintw(11, 1, "%s", state->jogoAtual.jogador.armaPrincipal.nome);

	// arma secundaria
	mvprintw(13, 1, "%s", "ARMA SECUNDARIA:");
	mvprintw(14, 1, "%s", state->jogoAtual.jogador.armaSecundaria.nome);

	// dinheiro
	mvprintw(16, 1, "%s", "DINHEIRO:");
	mvprintw(16, 10, "%d", state->jogoAtual.jogador.dinheiro);

	// num mapa atual
	mvprintw(3, (state->mapa.width - 43) / 2, "%s", "N U M E R O   M A P A    A T U A L   :   ");
	mvprintw(3, 115, "%d", state->jogoAtual.jogador.numMapaAtual);
}
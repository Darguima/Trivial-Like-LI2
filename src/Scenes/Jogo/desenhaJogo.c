#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "../../state.h"

void desenhaJogo(WINDOW *window, State *state, int x, int y, int **mapa)
{
	for (int i = 0; i < x; i++)
	{
		for (int n = 0; n < y; n++)
		{
			if (mapa[i][n] == 1)
			{
				mvwaddch(window, n, i, '#');
			}
			else
			{
				mvwaddch(window, n, i, ' ');
			}
		}
	}

	mvwaddch(window, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y, '@');
	wmove(window, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	wrefresh(window);

	return;
}

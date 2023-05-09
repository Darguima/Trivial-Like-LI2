#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "../../state.h"

int isokk(int x, int y, int xmax, int ymax)
{
	if (x >= 0 && x < xmax && y >= 0 && y < ymax)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// void verificablocosaolado( int posX, int posY, int maxX, int maxY, int **mapa) {

// }

void visao(int x, int y, int **mapa, int posX, int posY)
{
	for (int i = 0; i < x; i++)
	{
		for (int n = 0; n < y; n++)
		{
			if (mapa[i][n] == 1)
			{
				mapa[i][n] = 11;
			}
			else if (mapa[i][n] == 0)
			{
				mapa[i][n] = 10;
			}
		}
	}
	// se for visivel a parede passa para 1 e o chao para zero ;D

	for (int i = 0; i <= 360; i += 1)
	{
		float anguloRad;
		anguloRad = i * 0.017453;
		for (int j = 1; j <= 20; j++)
		{
			int blocoX, blocoY;

			blocoX = (posX + (j * cos(anguloRad)));
			blocoY = (posY - (j * sin(anguloRad)));
			if (!isokk(blocoX, blocoY, x, y))
			{
				break;
			}

			else if (mapa[blocoX][blocoY] == 10)
			{
				mapa[blocoX][blocoY] = 0;
			}
			else if (mapa[blocoX][blocoY] == 11 || mapa[blocoX][blocoY] == 1)
			{
				mapa[blocoX][blocoY] = 1;
				break;
			}
			// ! no segundo else if colocar || mapa[blocoX][blocoY] == 1 se nao funcionar
		}

		// ! criar variavel already found para cada ponto se sim ent vai ficar levemente colorido mas a variavel invisivel continua atia
	}
	// verificablocosaolado(posX, posY, x , y , mapa);
	return;
}

void desenhaJogo(WINDOW *window, State *state, int x, int y, int **mapa)
{
	visao(x, y, mapa, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	wrefresh(window);
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
				if (mapa[i][n] == 0)
				{
					mvwaddch(window, n, i, '.');
				}
				else
				{
					mvwaddch(window, n, i, ' ');
				}
			}
		}
	}
	mvwaddch(window, state->jogoAtual.jogador.posicao.y, state->jogoAtual.jogador.posicao.x, '@');
	wmove(window, state->jogoAtual.jogador.posicao.y, state->jogoAtual.jogador.posicao.x);
	wrefresh(window);

	return;
}

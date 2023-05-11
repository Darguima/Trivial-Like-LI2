#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "../state.h"

int isOk(int x, int y, int xmax, int ymax)
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

int is_pos_free(Mapa mapa, int x, int y)
{
	return isOk(x, y, mapa.width, mapa.height) && mapa.matrix[x][y].tipo != Parede;
}

void povoarMapa(int linhas, int colunas, ElementosDoMapa **mapa)
{
	for (int i = 0; i < linhas; i++)
	{
		for (int n = 0; n < (colunas); n++)
		{
			mapa[i][n].visivel = 1;

			if (i == 0 || i == linhas - 1 || n == 0 || (i == linhas - 1 && n == colunas - 1) || n == colunas - 1)
			{
				mapa[i][n].tipo = Parede;
			}
			else
			{

				int temp = rand() % 100;
				if (temp <= 42)
				{
					mapa[i][n].tipo = Parede;
				}
				else
				{
					mapa[i][n].tipo = Vazio;
				}
			}
		}
	}
	return;
}

void copyAll(int x, int y, ElementosDoMapa aqui[x][y], ElementosDoMapa **ali)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			aqui[i][j] = ali[i][j];
		}
	}
	return;
}

void applyCelular(int x, int y, ElementosDoMapa **mapa)
{
	for (int k = 0; k < 3; k++)
	{
		ElementosDoMapa auxMap[x][y];
		copyAll(x, y, auxMap, mapa);
		for (int s = 1; s < x; s++)
		{
			for (int j = 1; j < y; j++)
			{
				int window_count = 0;
				int window = 0;
				for (int a = s - 1; a <= s + 1; a++)
				{
					for (int b = j - 1; b <= j + 1; b++)
					{
						if (isOk(a, b, x, y))
						{

							if (auxMap[a][b].tipo == Parede)
							{
								window_count++;
							}
						}
						else
						{
							window_count++;
						}
					}
				}
				for (int a = s - 4; a <= s + 4; a++)
				{
					for (int b = j - 4; b <= j + 4; b++)
					{
						if (isOk(a, b, x, y))
						{

							if (auxMap[a][b].tipo == Parede)
							{
								window++;
							}
						}
						else
						{
							window++;
						}
					}
				}

				if (window_count >= 5 || window <= 2)
				{
					mapa[s][j].tipo = Parede;
				}
				else
				{
					mapa[s][j].tipo = Vazio;
				}
			}
		}
	}
	for (int k = 0; k < 2; k++)
	{
		ElementosDoMapa auxMap[x][y];
		copyAll(x, y, auxMap, mapa);
		for (int s = 1; s < x; s++)
		{
			for (int j = 1; j < y; j++)
			{
				int window_count = 0;
				for (int a = s - 1; a <= s + 1; a++)
				{
					for (int b = j - 1; b <= j + 1; b++)
					{
						if (isOk(a, b, x, y))
						{

							if (auxMap[a][b].tipo == Parede)
							{
								window_count++;
							}
						}
						else
						{
							window_count++;
						}
					}
				}

				if (window_count >= 5)
				{
					mapa[s][j].tipo = Parede;
				}
				else
				{
					mapa[s][j].tipo = Vazio;
				}
			}
		}
	}

	return;
}

void adicionarMoedas(State *state)
{
	int offset = (rand() % 5) - 2;
	for (int moedas_geradas = 0; moedas_geradas < 10 + offset; moedas_geradas++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.width - 2)) + 1;
			pos_y = (rand() % (state->mapa.height - 2)) + 1;
		} while (!is_pos_free(state->mapa, pos_x, pos_y));

		state->mapa.matrix[pos_x][pos_y].tipo = Moeda;
	}
}

void adicionarArmas(State *state)
{
	for (int armas_geradas = 0; armas_geradas < armasNoMapaLength; armas_geradas++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.width - 2)) + 1;
			pos_y = (rand() % (state->mapa.height - 2)) + 1;
		} while (!is_pos_free(state->mapa, pos_x, pos_y));

		Coordenadas pos = {pos_x, pos_y};
		state->jogoAtual.armas[armas_geradas].posicao = pos;
		state->jogoAtual.armas[armas_geradas].disponivel = 1;
		state->jogoAtual.armas[armas_geradas].arma = catalogoArmas[rand() % catalogoArmasLength];
	}
}

void adicionarMobs(State *state)
{
	for (int mobs_gerados = 0; mobs_gerados < mobsNoMapaLength; mobs_gerados++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.width - 2)) + 1;
			pos_y = (rand() % (state->mapa.height - 2)) + 1;
		} while (!is_pos_free(state->mapa, pos_x, pos_y));

		Coordenadas pos = {pos_x, pos_y};
		state->jogoAtual.mobs[mobs_gerados].posicao = pos;
		state->jogoAtual.mobs[mobs_gerados].mob = catalogoMobs[rand() % catalogoMobsLength];
	}
}

void geraMapa(State *state, int ncols, int nrows)
{
	int largura_mapa = ncols - 40;
	int altura_mapa = nrows - 10;

	povoarMapa(largura_mapa, altura_mapa, state->mapa.matrix);
	applyCelular(largura_mapa, altura_mapa, state->mapa.matrix);
	adicionarMoedas(state);
	adicionarArmas(state);
	adicionarMobs(state);

	int pos_x = 1;
	int pos_y = 1;

	int radius, x_offset = 0, y_offset = 0;

	for (radius = 1; radius < altura_mapa; radius++)
	{
		for (
				x_offset = radius, y_offset = 0;
				y_offset <= radius && !is_pos_free(state->mapa, pos_x + x_offset, pos_y + y_offset);
				y_offset++)
			;

		if (is_pos_free(state->mapa, pos_x + x_offset, pos_y + y_offset))
			break;

		for (
				y_offset = radius, x_offset = 0;
				x_offset <= radius && !is_pos_free(state->mapa, pos_x + x_offset, pos_y + y_offset);
				x_offset++)
			;

		if (is_pos_free(state->mapa, pos_x + x_offset, pos_y + y_offset))
			break;
	}

	state->jogoAtual.jogador.posicao.x = pos_x + x_offset;
	state->jogoAtual.jogador.posicao.y = pos_y + y_offset;

	return;
}
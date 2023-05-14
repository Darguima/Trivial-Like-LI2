#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "../state.h"
#include "../MapaUtils/mapaUtils.h"

void povoarMapa(int linhas, int colunas, ElementosDoMapa **mapa)
{
	for (int i = 0; i < linhas; i++)
	{
		for (int n = 0; n < (colunas); n++)
		{
			mapa[i][n].visivel = 1;
			mapa[i][n].descoberto = 0;

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
						if (estaDentroDoMapa(a, b, x, y))
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
						if (estaDentroDoMapa(a, b, x, y))
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
						if (estaDentroDoMapa(a, b, x, y))
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

// sinal deve ser 1 ou -1 para mudar o sinal do offset
// -1 vai aumentar a probabilidade de aparecer o elemento
// +1 vai diminuir a probabilidade de aparecer o elemento
int calcularProbabilidadeComDificuldade(int probabilidade, DificuldadeJogo dificuldade, int sinal)
{
	int result = (probabilidade + (probabilidade * dificuldade * 0.25 * sinal));
	return result > 0 ? result : 1;
}

void calcularQuantidadeElementosMapa(State *state)
{
	int area = state->mapa.matrix_height * state->mapa.matrix_width;
	DificuldadeJogo dificuldade = state->jogoAtual.dificuldade;

	// Probabilidade de aparecer uma arma = 1 / 3000
	state->mapa.qntArmasNoMapaLength = area / calcularProbabilidadeComDificuldade(3000, dificuldade, +1);
	free(state->jogoAtual.armas);
	state->jogoAtual.armas = malloc(state->mapa.qntArmasNoMapaLength * sizeof(ArmaNoMapa));

	// Probabilidade de aparecer uma arma = 1 / 1500
	state->mapa.qntObjetosNoMapaLength = area / calcularProbabilidadeComDificuldade(1500, dificuldade, +1);
	free(state->jogoAtual.objetos);
	state->jogoAtual.objetos = malloc(state->mapa.qntObjetosNoMapaLength * sizeof(ObjetoNoMapa));

	// Probabilidade de aparecer um mob = 1 / 600
	state->mapa.qntMobsNoMapaLength = area / calcularProbabilidadeComDificuldade(600, dificuldade, -1);
	free(state->jogoAtual.mobs);
	state->jogoAtual.mobs = malloc(state->mapa.qntMobsNoMapaLength * sizeof(MobNoMapa));

	// Probabilidade de aparecer uma moeda = 1 / 600
	state->mapa.qntMoedasNoMapaLength = area / calcularProbabilidadeComDificuldade(600, dificuldade, +1);
}

void adicionarMoedas(State *state)
{
	for (int moedas_geradas = 0; moedas_geradas < state->mapa.qntMoedasNoMapaLength; moedas_geradas++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.matrix_width - 2)) + 1;
			pos_y = (rand() % (state->mapa.matrix_height - 2)) + 1;
		} while (!estaTotalmenteLivre(state, pos_x, pos_y));

		state->mapa.matrix[pos_x][pos_y].tipo = Moeda;
	}
}

void adicionarArmas(State *state)
{
	for (int armas_geradas = 0; armas_geradas < state->mapa.qntArmasNoMapaLength; armas_geradas++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.matrix_width - 2)) + 1;
			pos_y = (rand() % (state->mapa.matrix_height - 2)) + 1;
		} while (!estaTotalmenteLivre(state, pos_x, pos_y));

		Coordenadas pos = {pos_x, pos_y};
		state->jogoAtual.armas[armas_geradas].posicao = pos;
		state->jogoAtual.armas[armas_geradas].disponivel = 1;
		state->jogoAtual.armas[armas_geradas].arma = catalogoArmas[rand() % catalogoArmasLength];
	}
}

void adicionarObjetos(State *state)
{
	for (int objetos_gerados = 0; objetos_gerados < state->mapa.qntObjetosNoMapaLength; objetos_gerados++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.matrix_width - 2)) + 1;
			pos_y = (rand() % (state->mapa.matrix_height - 2)) + 1;
		} while (!estaTotalmenteLivre(state, pos_x, pos_y));

		Coordenadas pos = {pos_x, pos_y};
		state->jogoAtual.objetos[objetos_gerados].posicao = pos;
		state->jogoAtual.objetos[objetos_gerados].objeto = catalogoObjetos[rand() % catalogoObjetosLength];
	}
}

void adicionarMobs(State *state)
{
	for (int mobs_gerados = 0; mobs_gerados < state->mapa.qntMobsNoMapaLength; mobs_gerados++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.matrix_width - 2)) + 1;
			pos_y = (rand() % (state->mapa.matrix_height - 2)) + 1;
		} while (!estaTotalmenteLivre(state, pos_x, pos_y));

		Coordenadas pos = {pos_x, pos_y};
		state->jogoAtual.mobs[mobs_gerados].posicao = pos;
		state->jogoAtual.mobs[mobs_gerados].mob = catalogoMobs[rand() % catalogoMobsLength];
	}
}

void geraMapa(State *state)
{
	int largura_mapa = state->mapa.matrix_width;
	int altura_mapa = state->mapa.matrix_height;

	// Gerar paredes
	povoarMapa(largura_mapa, altura_mapa, state->mapa.matrix);
	applyCelular(largura_mapa, altura_mapa, state->mapa.matrix);

	// Gerar Elementos
	calcularQuantidadeElementosMapa(state);

	adicionarMoedas(state);
	adicionarArmas(state);
	adicionarObjetos(state);
	adicionarMobs(state);

	// Encontrar uma posição livre para o user dar spawn
	int pos_x = 1;
	int pos_y = 1;

	int radius, x_offset = 0, y_offset = 0;

	for (radius = 1; radius < altura_mapa; radius++)
	{
		for (
				x_offset = radius, y_offset = 0;
				y_offset <= radius && !estaTotalmenteLivre(state, pos_x + x_offset, pos_y + y_offset);
				y_offset++)
			;

		if (estaTotalmenteLivre(state, pos_x + x_offset, pos_y + y_offset))
			break;

		for (
				y_offset = radius, x_offset = 0;
				x_offset <= radius && !estaTotalmenteLivre(state, pos_x + x_offset, pos_y + y_offset);
				x_offset++)
			;

		if (estaTotalmenteLivre(state, pos_x + x_offset, pos_y + y_offset))
			break;
	}

	state->jogoAtual.jogador.posicao.x = pos_x + x_offset;
	state->jogoAtual.jogador.posicao.y = pos_y + y_offset;

	return;
}
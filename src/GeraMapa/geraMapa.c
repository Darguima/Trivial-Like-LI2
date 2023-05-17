#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "../state.h"
#include "../MapaUtils/mapaUtils.h"

#include "../Scenes/GerandoMapa/desenhaGerandoMapa.h"

void povoarMapa(int linhas, int colunas, ElementosDoMapa **mapa, int mapa_desconhecido_ativo)
{
	for (int i = 0; i < linhas; i++)
	{
		for (int n = 0; n < (colunas); n++)
		{
			mapa[i][n].visivel = 1;
			mapa[i][n].descoberto = mapa_desconhecido_ativo ? 0 : 1;

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

void copyAll(int matrix_width, int matrix_height, ElementosDoMapa **src, ElementosDoMapa **dst)
{
	for (int x = 0; x < matrix_width; x++)
		for (int y = 0; y < matrix_height; y++)
			dst[x][y] = src[x][y];
}

void applyCelular(State *state, int matrix_width, int matrix_height)
{
	ElementosDoMapa **matrix = state->mapa.matrix;
	ElementosDoMapa **auxMap = alocar_matrix_mapa(matrix_width, matrix_height);

	for (int k = 0; k < 3; k++)
	{
		copyAll(matrix_width, matrix_height, matrix, auxMap);
		for (int x = 1; x < matrix_width; x++)
		{
			for (int y = 1; y < matrix_height; y++)
			{
				int window_count = 0;
				int window = 0;
				for (int a = x - 1; a <= x + 1; a++)
				{
					for (int b = y - 1; b <= y + 1; b++)
					{
						if (estaDentroDoMapa(a, b, matrix_width, matrix_height))
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
				for (int a = x - 4; a <= x + 4; a++)
				{
					for (int b = y - 4; b <= y + 4; b++)
					{
						if (estaDentroDoMapa(a, b, matrix_width, matrix_height))
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
					matrix[x][y].tipo = Parede;
				}
				else
				{
					matrix[x][y].tipo = Vazio;
				}
			}
		}
	}
	for (int k = 0; k < 2; k++)
	{
		copyAll(matrix_width, matrix_height, matrix, auxMap);
		for (int x = 1; x < matrix_width; x++)
		{
			for (int y = 1; y < matrix_height; y++)
			{
				int window_count = 0;
				for (int a = x - 1; a <= x + 1; a++)
				{
					for (int b = y - 1; b <= y + 1; b++)
					{
						if (estaDentroDoMapa(a, b, matrix_width, matrix_height))
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
					matrix[x][y].tipo = Parede;
				}
				else
				{
					matrix[x][y].tipo = Vazio;
				}
			}
		}
	}

	libertar_matrix_mapa(auxMap, matrix_width);
}

// sinal deve ser 1 ou -1 para mudar o sinal do offset
// -1 vai aumentar a probabilidade de aparecer o elemento
// +1 vai diminuir a probabilidade de aparecer o elemento
int calcularQuantidadeComDificuldade(int area, int probabilidade, DificuldadeJogo dificuldade, int sinal)
{
	int probabilidade_final = (probabilidade + (probabilidade * dificuldade * 0.25 * sinal));

	int quantidade = area / probabilidade_final;

	return quantidade > 0 ? quantidade : 1;
}

void calcularQuantidadeElementosMapa(State *state)
{
	int area = state->mapa.matrix_height * state->mapa.matrix_width;
	DificuldadeJogo dificuldade = state->jogoAtual.dificuldade;

	// Probabilidade de aparecer uma arma = 1 / 3000
	state->mapa.qntArmasNoMapaLength = calcularQuantidadeComDificuldade(area, 3000, dificuldade, +1);
	free(state->jogoAtual.armas);
	state->jogoAtual.armas = malloc(state->mapa.qntArmasNoMapaLength * sizeof(ArmaNoMapa));

	// Probabilidade de aparecer uma arma = 1 / 1500
<<<<<<< HEAD
	state->mapa.qntObjetosNoMapaLength = area / calcularProbabilidadeComDificuldade(1500, dificuldade, +1);
=======
	state->mapa.qntObjetosNoMapaLength = calcularQuantidadeComDificuldade(area, 1500, dificuldade, +1);
>>>>>>> eed931ca12c1ac2b107966dc10c7cde5e43994cb
	free(state->jogoAtual.objetos);
	state->jogoAtual.objetos = malloc(state->mapa.qntObjetosNoMapaLength * sizeof(ObjetoNoMapa));

	// Probabilidade de aparecer um mob = 1 / 600
	state->mapa.qntMobsNoMapaLength = calcularQuantidadeComDificuldade(area, 600, dificuldade, -1);
	free(state->jogoAtual.mobs);
	state->jogoAtual.mobs = malloc(state->mapa.qntMobsNoMapaLength * sizeof(MobNoMapa));

	// Probabilidade de aparecer uma moeda = 1 / 600
	state->mapa.qntMoedasNoMapaLength = calcularQuantidadeComDificuldade(area, 600, dificuldade, +1);

	// Probabilidade de aparecer uma portal = 1 / 45000
	state->mapa.qntPortaisNoMapaLength = calcularQuantidadeComDificuldade(area, 45000, dificuldade, +1);
}

void adicionarPortais(State *state)
{
	int portalX = 0;
	int portalY = 0;
	int distance,
			min_distance = (state->mapa.matrix_width + state->mapa.matrix_height) / 4;

	for (int portais_gerados = 0; portais_gerados < state->mapa.qntPortaisNoMapaLength; portais_gerados++)
	{
		int pos_x, pos_y;

		do
		{
			pos_x = (rand() % (state->mapa.matrix_width - 2)) + 1;
			pos_y = (rand() % (state->mapa.matrix_height - 2)) + 1;
			distance = sqrt(pow(abs(pos_x - state->mapa.matrix_width / 2), 2) + pow(abs(pos_y - state->mapa.matrix_height / 2), 2));

		} while (
				!estaSemParede(state->mapa, pos_x, pos_y) ||
				!estaSemParede(state->mapa, pos_x + 1, pos_y) ||
				!estaSemParede(state->mapa, pos_x + 2, pos_y) ||
				!estaSemParede(state->mapa, pos_x, pos_y + 1) ||
				!estaSemParede(state->mapa, pos_x + 1, pos_y + 1) ||
				!estaSemParede(state->mapa, pos_x + 2, pos_y + 1) ||
				!estaSemParede(state->mapa, pos_x, pos_y + 2) ||
				!estaSemParede(state->mapa, pos_x + 1, pos_y + 2) ||
				!estaSemParede(state->mapa, pos_x + 2, pos_y + 2) ||
				distance < min_distance);

		portalX = pos_x;
		portalY = pos_y;

		state->mapa.matrix[portalX][portalY].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 1][portalY].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 2][portalY].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX][portalY + 1].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 1][portalY + 1].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 2][portalY + 1].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX][portalY + 2].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 1][portalY + 2].tipo = PortaProximoMapa;
		state->mapa.matrix[portalX + 2][portalY + 2].tipo = PortaProximoMapa;
	}
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
		// Primeiro elementos do catalogoArmas são os punhos
		state->jogoAtual.armas[armas_geradas].arma = catalogoArmas[(rand() % (catalogoArmasLength - 1)) + 1];
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
		state->jogoAtual.objetos[objetos_gerados].disponivel = 1;
		state->jogoAtual.objetos[objetos_gerados].objeto = catalogoObjetos[rand() % catalogoObjetosLength];
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
		state->jogoAtual.objetos[objetos_gerados].disponivel = 1;
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

// Encontrar uma posição livre para o user dar spawn
void encontrarPosicaoLivreUser(State *state)
{
	int pos_x = state->mapa.matrix_width / 2;
	int pos_y = state->mapa.matrix_height / 2;

	int x_offset;
	for (
			x_offset = 0;
			x_offset < state->mapa.matrix_width / 2 && !estaTotalmenteLivreParaOUser(state, pos_x + x_offset, pos_y);
			x_offset++)
		;

	state->jogoAtual.jogador.posicao.x = pos_x + x_offset;
	state->jogoAtual.jogador.posicao.y = pos_y;
}

void geraMapa(State *state)
{
	werase(state->ncurses_screen);
	desenhaGerandoMapa(state->ncurses_screen, "A povoar Mapa com paredes.");

	int largura_mapa = state->mapa.matrix_width;
	int altura_mapa = state->mapa.matrix_height;

	// Gerar paredes
<<<<<<< HEAD
	povoarMapa(largura_mapa, altura_mapa, state->mapa.matrix);
	applyCelular(largura_mapa, altura_mapa, state->mapa.matrix);
=======
	povoarMapa(largura_mapa, altura_mapa, state->mapa.matrix, state->jogoAtual.mapa_desconhecido_ativo);
	applyCelular(state, largura_mapa, altura_mapa);

	// Gerar Elementos
	desenhaGerandoMapa(state->ncurses_screen, "Calcular quantidades de elementos do mapa.");
>>>>>>> eed931ca12c1ac2b107966dc10c7cde5e43994cb

	// Gerar Elementos
	calcularQuantidadeElementosMapa(state);

	desenhaGerandoMapa(state->ncurses_screen, "A adicionar portais ao mapa.");
	adicionarPortais(state);
	desenhaGerandoMapa(state->ncurses_screen, "A adicionar moedas ao mapa.");
	adicionarMoedas(state);
	desenhaGerandoMapa(state->ncurses_screen, "A adicionar armas ao mapa.");
	adicionarArmas(state);
<<<<<<< HEAD
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
=======
	desenhaGerandoMapa(state->ncurses_screen, "A adicionar objetos ao mapa.");
	adicionarObjetos(state);
	desenhaGerandoMapa(state->ncurses_screen, "A adicionar mobs ao mapa.");
	adicionarMobs(state);

	desenhaGerandoMapa(state->ncurses_screen, "A encontrar uma posição para dar spawn.");
	encontrarPosicaoLivreUser(state);
>>>>>>> eed931ca12c1ac2b107966dc10c7cde5e43994cb
}
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

void povoarMapa(int linhas, int colunas, int **mapa)
{
	srand(time(NULL));
	for (int i = 0; i < linhas; i++)
	{
		for (int n = 0; n < (colunas); n++)
		{
			if (i == 0 || i == linhas - 1 || n == 0 || (i == linhas - 1 && n == colunas - 1) || n == colunas - 1)
			{
				mapa[i][n] = 1;
			}
			else
			{

				int temp = rand() % 100;
				if (temp <= 42)
				{
					mapa[i][n] = 1;
				}
				else
				{
					mapa[i][n] = 0;
				}
			}
		}
	}
	return;
}

void copyAll(int x, int y, int aqui[x][y], int **ali)
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

void applyCelular(int x, int y, int **mapa)
{
	for (int k = 0; k < 3; k++)
	{
		int auxMap[x][y];
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

							if (auxMap[a][b] == 1)
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

							if (auxMap[a][b] == 1)
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
					mapa[s][j] = 1;
				}
				else
				{
					mapa[s][j] = 0;
				}
			}
		}
	}
	for (int k = 0; k < 2; k++)
	{
		int auxMap[x][y];
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

							if (auxMap[a][b] == 1)
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
					mapa[s][j] = 1;
				}
				else
				{
					mapa[s][j] = 0;
				}
			}
		}
	}

	return;
}

void geraMapa(int ncols, int nrows, int **mapa)
{

	povoarMapa(ncols - 40, nrows - 10, mapa);
	applyCelular(ncols - 40, nrows - 10, mapa);

	return;
}
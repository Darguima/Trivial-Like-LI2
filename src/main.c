#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "state.h"

#include "Scenes/MenuInicial/desenhaMenuInicial.h"
#include "Scenes/MenuInicial/eventosMenuInicial.h"

#include "Scenes/SelecionarJogador/desenhaSelecionarJogador.h"
#include "Scenes/SelecionarJogador/eventosSelecionarJogador.h"

#include "Scenes/Jogo/desenhaJogo.h"
#include "Scenes/Jogo/eventosJogo.h"

#include "Scenes/Controlos/desenhaControlos.h"
#include "Scenes/Controlos/eventosControlos.h"

#include "Scenes/Sobre/desenhaSobre.h"
#include "Scenes/Sobre/eventosSobre.h"

#include "Scenes/Sair/desenhaSair.h"
#include "Scenes/Sair/eventosSair.h"

#include "Scenes/GameOver/desenhaGameOver.h"
#include "Scenes/GameOver/eventosGameOver.h"

int main()
{
	WINDOW *window = initscr();

	int nrows, ncols;
	getmaxyx(window, nrows, ncols);
	State state = criarEstado(ncols, nrows);

	/* Configuring Window */
	srand48(time(NULL));
	srand(time(NULL));
	// Desativa o cursor do ecrã
	curs_set(0);

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	/* Starting colors & colors pairs */
	start_color();

	init_color(FG_MapaVisivel, 1000, 1000, 1000);
	init_color(FG_MapaMemoria, 250, 250, 250);
	init_color(FG_MapaDesconhecido, 100, 100, 100);

	init_color(BG_MapaVisivel, 250, 250, 250);
	init_color(BG_MapaMemoria, 150, 150, 150);
	init_color(BG_MapaDesconhecido, 125, 125, 125);

	init_color(FG_Player, 0, 0, 1000);
	init_color(FG_Moeda, 1000, 1000, 0);
	init_color(FG_Arma, 0, 1000, 0);
	init_color(FG_Objeto, 0, 0, 1000);
	init_color(FG_Mob, 1000, 0, 0);

	init_pair(WhiteBlack, COLOR_WHITE, COLOR_BLACK);
	init_pair(YellowBlack, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BlueBlack, COLOR_BLUE, COLOR_BLACK);
	init_pair(GreenBlack, COLOR_GREEN, COLOR_BLACK);
	init_pair(BlackYellow, COLOR_BLACK, COLOR_YELLOW);
	init_pair(BlackRed, COLOR_BLACK, COLOR_RED);
	init_pair(RedBlack, COLOR_RED, COLOR_BLACK);

	init_pair(MapaPlayerColor, FG_Player, BG_MapaVisivel);

	init_pair(MapaVisivelColor, FG_MapaVisivel, BG_MapaVisivel);
	init_pair(MapaMemoriaColor, FG_MapaMemoria, BG_MapaMemoria);
	init_pair(MapaDesconhecidoColor, FG_MapaDesconhecido, BG_MapaDesconhecido);

	init_pair(MoedaColor, FG_Moeda, BG_MapaVisivel);
	init_pair(ArmaColor, FG_Arma, BG_MapaVisivel);
	init_pair(ObjetoColor, FG_Objeto, BG_MapaVisivel);
	init_pair(MobColor, FG_Mob, BG_MapaVisivel);

	init_pair(ArmaBox, FG_Arma, COLOR_BLACK);
	init_pair(ObjetoBox, FG_Objeto, COLOR_BLACK);
	init_pair(MobBox, FG_Mob, COLOR_BLACK);

	WINDOW *janela_do_jogo = newwin(nrows - 10, ncols - 40, 5, 20);

	Scene sceneAnterior = state.sceneAtual;

	while (1)
	{
		/* Limpar o conteúdo do terminal caso se tenha alterado a scene */
		if (state.sceneAtual != sceneAnterior)
		{
			for (int x = 0; x < ncols; x++)
				for (int y = 0; y < nrows; y++)
					mvaddch(y, x, ' ');

			sceneAnterior = state.sceneAtual;
		}

		switch (state.sceneAtual)
		{
		case MenuInicial:
			desenhaMenuInicial(window, &state);
			eventosMenuInicial(&state);
			break;

		case SelecionarJogador:
			desenhaSelecionarJogador(window, &state);
			eventosSelecionarJogador(&state);

			break;

		case Jogo:
			wrefresh(window);
			desenhaMenusLaterais(window, &state);
			desenhaJogo(janela_do_jogo, &state);
			eventosJogo(&state);

			break;

		case Controlos:
			desenhaControlos(window, &state);
			eventosControlos(&state);
			break;

		case Sobre:
			desenhaSobre(window, &state);
			eventosSobre(&state);
			break;

		case Sair:
			desenhaSair(window, &state);
			eventosSair(&state);
			break;

		case GameOver:
			desenhaGameOver(window, &state);
			eventosGameOver(&state);
		}

		move(0, 0);
	}

	return 0;
}

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

int main()
{

	WINDOW *window = initscr();

	int nrows, ncols;
	getmaxyx(window, nrows, ncols);

	State state = criarEstado(ncols, nrows);

	/* Configuring Window */
	srand48(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	/* Starting colors pairs */
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

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
			desenhaJogo(janela_do_jogo, &state, ncols - 40, nrows - 10, state.mapa.matrix);
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
		}

		move(0, 0);
	}

	return 0;
}

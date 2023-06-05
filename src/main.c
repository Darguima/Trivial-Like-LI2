#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
#include "state.h"
#include "colors.h"

#include "Scenes/MenuInicial/desenhaMenuInicial.h"
#include "Scenes/MenuInicial/eventosMenuInicial.h"

#include "Scenes/SelecionarJogador/desenhaSelecionarJogador.h"
#include "Scenes/SelecionarJogador/eventosSelecionarJogador.h"

#include "Scenes/Jogo/desenhaJogo.h"
#include "Scenes/Jogo/eventosJogo.h"

#include "Scenes/GameOver/desenhaGameOver.h"
#include "Scenes/GameOver/eventosGameOver.h"

#include "Scenes/Definicoes/desenhaDefinicoes.h"
#include "Scenes/Definicoes/eventosDefinicoes.h"

#include "Scenes/Controlos/desenhaControlos.h"
#include "Scenes/Controlos/eventosControlos.h"

#include "Scenes/Sobre/desenhaSobre.h"
#include "Scenes/Sobre/eventosSobre.h"

#include "Scenes/Sair/desenhaSair.h"
#include "Scenes/Sair/eventosSair.h"

int main()
{
	// Active unicode chars
	setlocale(LC_ALL, "");

	WINDOW *window = initscr();

	/* Configuring Window */
	srand48(time(NULL));
	srand(time(NULL));
	curs_set(0);
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	/* Iniciar e definir as nossas cores*/
	start_state_colors();

	/* Criar um estado ss*/
	int n_linhas, n_colunas;
	getmaxyx(window, n_linhas, n_colunas);
	State state = criarEstado(window, n_colunas, n_linhas);

	Scene sceneAnterior = state.sceneAtual;
	WINDOW *window_game = newwin(n_linhas - 10, n_colunas - 40, 5, 20);

	while (1)
	{
		if (state.sceneAtual != sceneAnterior)
		{
			werase(window);
			sceneAnterior = state.sceneAtual;
		}

		// Existe uma scene, GerandoMapa, que não é renderizada por aqui; é renderizada pela GeraMapa
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
			desenhaJogo(window_game, &state);
			eventosJogo(&state);
			break;

		case GameOver:
			desenhaGameOver(window, &state);
			eventosGameOver(&state);
			break;

		case Definicoes:
			desenhaDefinicoes(window, &state);
			eventosDefinicoes(&state);
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
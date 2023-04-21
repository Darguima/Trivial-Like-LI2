#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"

#include "Scenes/MenuInicial/desenhaMenuInicial.h"
#include "Scenes/MenuInicial/eventosMenuInicial.h"

#include "Scenes/Jogo/desenhaJogo.h"
#include "Scenes/Jogo/eventosJogo.h"

int main() {
	State state = criarEstado();

	WINDOW *window = initscr();

	/* Configuring Window */
	srand48(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
  move(0, 0);

	/* Starting colors pairs */
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

	while(1) {
		switch (state.sceneAtual)
		{
			case MenuInicial:
				desenhaMenuInicial(window, &state);
				eventosMenuInicial(&state);
				break;
			
			case SelecionarJogador:
				desenhaMenuInicial(window, &state);
				eventosMenuInicial(&state);
				break;
			
			case Jogo:
				desenhaJogo(window, &state);
				eventosJogo(&state);
				break;

			case Controlos:
				desenhaMenuInicial(window, &state);
				eventosMenuInicial(&state);
				break;
			
			case Sobre:
				desenhaMenuInicial(window, &state);
				eventosMenuInicial(&state);
				break;

			case Sair:
				desenhaMenuInicial(window, &state);
				eventosMenuInicial(&state);
				break;
		}
	}

	return 0;
}

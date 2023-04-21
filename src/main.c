#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#include "state.h"
#include "mapa.h"

void do_movement_action(State *state, int dx, int dy) {
	state->jogoAtual.jogador.posicao.x += dx;
	state->jogoAtual.jogador.posicao.y += dy;
}

void update(State *state) {
	int key = getch();

	mvaddch(state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y, ' ');

	switch(key) {
		case KEY_A1:
		case '7': do_movement_action(state, -1, -1); break;
		case KEY_UP:
		case '8': do_movement_action(state, -1, +0); break;
		case KEY_A3:
		case '9': do_movement_action(state, -1, +1); break;
		case KEY_LEFT:
		case '4': do_movement_action(state, +0, -1); break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6': do_movement_action(state, +0, +1); break;
		case KEY_C1:
		case '1': do_movement_action(state, +1, -1); break;
		case KEY_DOWN:
		case '2': do_movement_action(state, +1, +0); break;
		case KEY_C3:
		case '3': do_movement_action(state, +1, +1); break;
		case 'q': endwin(); exit(0); break;
	}
}

int main() {
	State state = criarEstado();

	WINDOW *window = initscr();
	int ncols, nrows;
	getmaxyx(window,nrows,ncols);

	srand48(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);

	while(1) {
		attron(COLOR_PAIR(COLOR_BLUE));
		for(int i = 0 ; i < nrows ; i++) {
			for (int n = 0 ; n < ncols ; n++) {
				mvaddch(i, n, '#' | A_DIM);
			}
		}
		attroff(COLOR_PAIR(COLOR_BLUE));


		attron(COLOR_PAIR(COLOR_WHITE));
		mvaddch(state.jogoAtual.jogador.posicao.x, state.jogoAtual.jogador.posicao.y, 'p');
		attroff(COLOR_PAIR(COLOR_WHITE));

		move(0, 0);
		update(&state);
	}

	return 0;
}

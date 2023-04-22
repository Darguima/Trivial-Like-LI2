#include <ncurses.h>

#include "../../state.h"

void desenhaJogo(WINDOW* window, State* state) {
  int nrows, ncols;
	getmaxyx(window, nrows, ncols);

  attron(COLOR_PAIR(COLOR_BLUE));
  for(int i = 0 ; i < nrows ; i++) {
    for (int n = 0 ; n < ncols ; n++) {
      mvaddch(i, n, '#' | A_DIM);
    }
  }
  attroff(COLOR_PAIR(COLOR_BLUE));


  attron(COLOR_PAIR(COLOR_WHITE));
  mvaddch(state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y, 'p');
  attroff(COLOR_PAIR(COLOR_WHITE));
}

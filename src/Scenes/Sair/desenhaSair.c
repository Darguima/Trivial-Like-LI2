#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSair(WINDOW* window, State* state) {
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
	getmaxyx(window, nrows, ncols);

  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  box(window, 0, 0); // desenhar caixa

  mvaddstr(y, x-4, "Deseja mesmo sair?");
  mvaddstr(y+2, x-12, "O jogo ainda tem tanto para dar...");

  mvaddstr(nrows - 4, 2, "Pressione 's' para sair");
  mvaddstr(nrows - 2, 2, "Pressione 'q' para voltar ao menu anterior");
}
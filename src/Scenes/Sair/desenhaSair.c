#include <ncurses.h>

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

  mvaddstr((nrows / 2) - 2, (ncols - 18) / 2, "Neste menu vai ser");
  mvaddstr((nrows / 2) - 1, (ncols - 25) / 2, "confirmado a acao de sair");
  mvaddstr((nrows / 2) + 1, (ncols - 19) / 2, "press v para voltar");
  mvaddstr((nrows / 2) + 2, (ncols - 17) / 2, "press q para sair");
}
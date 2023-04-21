#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaMenuInicial(WINDOW* window, State* state) {
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
	getmaxyx(window, nrows, ncols);

  mvaddstr((nrows / 2) - 2, (ncols - 18) / 2, "press j para jogar");
  mvaddstr((nrows / 2) - 1, (ncols - 26) / 2, "press c para ver controlos");
  mvaddstr((nrows / 2) - 0, (ncols - 22) / 2, "press s para ver sobre");
  mvaddstr((nrows / 2) + 1, (ncols - 17) / 2, "press q para sair");
}
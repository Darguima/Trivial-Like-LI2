#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSelecionarJogador(WINDOW* window, State* state) {
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
	getmaxyx(window, nrows, ncols);

  mvaddstr((nrows / 2) - 2, (ncols - 43) / 2, "Neste menu vai ser possivel escolher o save");
  mvaddstr((nrows / 2) + 0, (ncols - 18) / 2, "press j para jogar");
  mvaddstr((nrows / 2) + 1, (ncols - 19) / 2, "press q para voltar");
}
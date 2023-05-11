#include <ncurses.h>

#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSelecionarJogador(WINDOW *window, State *state)
{
  UNUSED(window);
  UNUSED(state);

  geraMapa(state, state->mapa.terminal.width, state->mapa.terminal.height);

  int nrows, ncols;
  getmaxyx(stdscr, nrows, ncols);
  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  box(window, 0, 0); // desenhar caixa

  refresh();

  mvaddstr(y, x - 17, "Escolher o save");
  mvaddstr(nrows - 4, 2, "Pressione [J] para jogar");
  mvaddstr(nrows - 2, 2, "Pressione [Q] para voltar");
}
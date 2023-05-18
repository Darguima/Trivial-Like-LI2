#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSobre(WINDOW *window, State *state)
{
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
  getmaxyx(window, nrows, ncols);

  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  box(window, 0, 0); // desenhar caixa

  mvwprintw(window, y - 1, x - 20, "TriviaLike e um jogo criado com base no 'Rogue',");
  mvwprintw(window, y    , x - 20, "um jogo lançado em 1980 que deu origem a todo um");
  mvwprintw(window, y + 1, x - 22, "genero, que se subdivide em roguelikes e roguelites.");
  mvwprintw(window, y + 2, x - 17, "Este e um jogo criado por um grupo de colegas");
  mvwprintw(window, y + 3, x - 18, "universitarios com o fim de realizar um projeto");
  mvwprintw(window, y + 4, x - 10, "na linguagem de programação C.");

  mvwprintw(window, y + 8, x - 12, "Hugo Rauber       Afonso Pedreira");
  mvwprintw(window, y + 10, x - 12, "Rodrigo Macedo    Dario Guimaraes");

  mvwprintw(window, nrows - 2, 2, "Pressiona [Q] para voltar");
}
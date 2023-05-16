#include <ncurses.h>
#include <string.h>

void desenhaGerandoMapa(WINDOW *window, char *status)
{
  int nrows, ncols;
  getmaxyx(window, nrows, ncols);

  int y = (nrows / 2);
  int x = (ncols / 2);

  move(y, 0);
  clrtoeol();
  mvwprintw(window, y, x - (strlen(status) / 2), status);
  
  box(window, 0, 0); // desenhar caixa

	refresh();
}
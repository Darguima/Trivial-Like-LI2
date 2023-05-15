#include <ncurses.h>

#include "../../state.h"

#define UNUSED(x) (void)(x)

void desenhaMenuInicial(WINDOW *window, State *state)
{
    UNUSED(window);
    UNUSED(state);
    noecho();

    int nrows, ncols;
    getmaxyx(stdscr, nrows, ncols);
    int y = (nrows / 2) - 4;
    int x = (ncols / 2) - 2;

    refresh();

    box(window, 0, 0); // desenhar caixa

    mvaddstr(y, x - 5, "1.Selecionar jogador");
    mvaddstr(y + 3, x - 3, "2.Definições");
    mvaddstr(y + 6, x - 2, "3.Controlos");
    mvaddstr(y + 9, x - 1, "4.Sobre");
    mvaddstr(y + 12, x, "5.Sair");
    mvaddstr(nrows - 2, 2, "Selecione a opção com [1]-[5]");

    mvprintw(y - 7, x - 21, "     _____     _       _       _ _ _            ");
    mvprintw(y - 6, x - 21, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
    mvprintw(y - 5, x - 21, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
    mvprintw(y - 4, x - 21, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
    mvprintw(y - 3, x - 21, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___| ");
}

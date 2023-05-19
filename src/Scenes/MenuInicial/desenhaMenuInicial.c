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
    int y = (nrows / 2);
    int x = (ncols / 2);

    refresh();

    mvprintw(y - 11, x - 24, "     _____     _       _       _ _ _           ");
    mvprintw(y - 10, x - 24, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
    mvprintw(y - 9, x - 24, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
    mvprintw(y - 8, x - 24, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
    mvprintw(y - 7, x - 24, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___|   ");

    mvaddstr(y - 4, x - 10, "1.Selecionar jogador");
    mvaddstr(y - 1, x - 7, "2.Definicoes");
    mvaddstr(y + 2, x - 6, "3.Controlos");
    mvaddstr(y + 5, x - 4, "4.Sobre");
    mvaddstr(y + 8, x - 4, "5.Sair");
    mvaddstr(nrows - 2, 2, "Seleciona a opcao com [1]-[5]");

    box(window, 0, 0); // desenhar caixa
}

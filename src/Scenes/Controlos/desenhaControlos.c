#include <ncurses.h>
#include "../../state.h"
#include "desenhaControlos.h"
/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void print_menu(WINDOW *win, char options[][MAX_OPTION_LEN], int num_options, int highlight, int side, int help);

void desenhaControlos(WINDOW *window, State *state)
{
    UNUSED(state);

    char options[NUM_OPTIONS][MAX_OPTION_LEN] = {"Mover  cima", "Mover  baixo", "Mover  esquerda", "Mover  direita", "Sair"};
    refresh();

    print_menu(window, options, NUM_OPTIONS, state->scenesVariables.controlosSceneVars.highlight, state->scenesVariables.controlosSceneVars.side, state->scenesVariables.controlosSceneVars.help);
}
void print_menu(WINDOW *win, char options[][MAX_OPTION_LEN], int num_options, int highlight, int side, int help)
{
    int x, y, z, i;
    box(win, 0, 0); // draw border
    if (side == 0)
    {
        for (i = 0; i < num_options; i++)
        {
            z = 2 * i + 1;
            y = i + 1;
            x = 2;
            if (highlight == y)
            {
                wattron(win, A_REVERSE); // highlight current option
            }
            mvwaddstr(win, z, x, options[i]);
            if (highlight == y)
            {
                wattroff(win, A_REVERSE); // turn off highlight
            }
        }
    }
    // botao help para side 1
    mvwaddstr(win, 1, COLS - 10, "Ajuda");
    if (side == 1)
    {
        for (i = 0; i < num_options; i++)
        { // imprimir opcoes outra vez para remover highlight para quando side é 1
            z = 2 * i + 1;
            y = i + 1;
            x = 2;
            mvwaddstr(win, z, x, options[i]);
        }
        wattron(win, A_REVERSE);
        mvwaddstr(win, 1, COLS - 10, "Ajuda");
        wattroff(win, A_REVERSE);
        mvwprintw(win, 28, 76, " ");
    }

    // print arrow or 'q' based on selection
    if (side == 0)
    {
        switch (highlight)
        {
        case 1:
            mvwprintw(win, LINES / 2 + 10, COLS / 2 - 12, "->    Up arrow   <-");
            mvwprintw(win, LINES / 2 - 5, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 4, COLS / 2 - 5, " ...  ");
            mvwprintw(win, LINES / 2 - 3, COLS / 2 - 5, "..... ");
            mvwprintw(win, LINES / 2 - 2, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 1, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2    , COLS / 2 - 5, "  .   ");
            mvwprintw(win, 28, 76, " "); // por entrada de texto num sitio porreiro

            break;
        case 2:
            mvwprintw(win, LINES / 2 + 10, COLS / 2 - 12, "->   Down arrow  <-");
            mvwprintw(win, LINES / 2 - 5, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 4, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 3, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 2, COLS / 2 - 5, "..... ");
            mvwprintw(win, LINES / 2 - 1, COLS / 2 - 5, " ...  ");
            mvwprintw(win, LINES / 2   , COLS / 2 - 5,  "  .   ");
            mvwprintw(win, 28, 76, " ");
            break;
        case 3:
            mvwprintw(win, LINES / 2 + 10, COLS / 2 - 12, "->   Left arrow  <-");
            mvwprintw(win, LINES / 2 - 5, COLS / 2 - 5, "      ");
            mvwprintw(win, LINES / 2 - 4, COLS / 2 - 5, "   .  ");
            mvwprintw(win, LINES / 2 - 3, COLS / 2 - 5, "   .. ");
            mvwprintw(win, LINES / 2 - 2, COLS / 2 - 5, "......");
            mvwprintw(win, LINES / 2 - 1, COLS / 2 - 5, "   .. ");
            mvwprintw(win, LINES / 2    , COLS / 2 - 5, "   . ");
            mvwprintw(win, 28, 76, " ");
            break;
        case 4:
            mvwprintw(win, LINES / 2 + 10, COLS / 2 - 12, "->  Right arrow  <-");
            mvwprintw(win, LINES / 2 - 5, COLS / 2 - 5, "      ");
            mvwprintw(win, LINES / 2 - 4, COLS / 2 - 5, "  .   ");
            mvwprintw(win, LINES / 2 - 3, COLS / 2 - 5, " ..   ");
            mvwprintw(win, LINES / 2 - 2, COLS / 2 - 5, "......");
            mvwprintw(win, LINES / 2 - 1, COLS / 2 - 5, " ..   ");
            mvwprintw(win, LINES / 2    , COLS / 2 - 5, "  .   ");
            mvwprintw(win, 28, 76, " ");
            break;
        case 5:
            mvwprintw(win, LINES / 2 + 10, COLS / 2 - 12, "->    Press Q    <-");
            mvwprintw(win, LINES / 2 - 5, COLS / 2 - 5, "......");
            mvwprintw(win, LINES / 2 - 4, COLS / 2 - 5, ".    .");
            mvwprintw(win, LINES / 2 - 3, COLS / 2 - 5, "......");
            mvwprintw(win, LINES / 2 - 2, COLS / 2 - 5, "     .");
            mvwprintw(win, LINES / 2 - 1, COLS / 2 - 5, "     .");
            mvwprintw(win, LINES / 2    , COLS / 2 - 5, "     .");
            mvwprintw(win, 28, 76, " ");
            break;
        default:
            break;
        }
    }
    if (help == 1)
    {
        
        mvwprintw(win, LINES-3, 2, "Pressiona [Q] para voltar");
        mvwprintw(win, 28, 76, " ");
    }
    if (help == 0)
    {
        mvwprintw(win, LINES-3, 2, "                         ");
        mvwprintw(win, 28, 76, " ");
    }

    wrefresh(win); // refresh window
}

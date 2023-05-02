#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "../../state.h"

#define UNUSED(x) (void)(x)

typedef struct MenuStruct
{
    char texto[100]; // texto do menu
    int y_inicial;   // o menu começa na posição y
    int x_inicial;   // o menu começa na posição x
    char trigger;    // tecla que dá trigger à ação

} Menu;

void desenhaInicializacao(WINDOW *win, Menu menus[], int n_menus)
{
    for (int i = 0; i < n_menus; i++)
    {
        mvwprintw(win, menus[i].y_inicial, menus[i].x_inicial, "%s", menus[i].texto);
    }
}

void limpaEcra(WINDOW *win, int y, int x)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            mvwprintw(win, i, j, " ");
        }
    }
    box(win, 0, 0);
}

void desenhaEventos(WINDOW *win, Menu menus[], int n_menus, int cor, char key)
{

    int menu_atual = -1;

    for (int i = 0; i < n_menus; i++)
    {
        if (key == menus[i].trigger)
        {
            wattron(win, COLOR_PAIR(cor) | A_STANDOUT);
            mvwprintw(win, menus[i].y_inicial, menus[i].x_inicial, "%s", menus[i].texto);
            wattroff(win, COLOR_PAIR(cor) | A_STANDOUT);
            menu_atual = i;
        }
    }

    for (int i = 0; i < n_menus; i++)
    {
        if (i != menu_atual)
        {
            mvwprintw(win, menus[i].y_inicial, menus[i].x_inicial, "%s", menus[i].texto);
        }
    }

    if (key == '4')
    {
        wattron(win, COLOR_PAIR(cor) | A_STANDOUT);
        mvwprintw(win, (menus[n_menus - 1].y_inicial) + 2, (menus[n_menus - 1].x_inicial) - 6, "Deseja Sair? (s/n) ");
        wattroff(win, COLOR_PAIR(cor) | A_STANDOUT);
    }
}

void desenhaSobre1(WINDOW *win, int y)
{
    mvwprintw(win, y, 1, " Pressione ESC para voltar atrás ");
    mvwprintw(win, 2, 2, "TriviaLike é um jogo criado com base no 'Rogue',");
    mvwprintw(win, 3, 2, "um jogo lançado em 1980 que deu origem a todo um");
    mvwprintw(win, 4, 2, "género, que se subdivide em rogue-like e lite.");
    mvwprintw(win, 6, 2, "Este é um jogo criado por um grupo de colegas");
    mvwprintw(win, 7, 2, "universitários, com o fim de realizar um projeto");
    mvwprintw(win, 8, 2, "em C.");
    mvwprintw(win, 10, 2, "Hugo Rauber       Afonso Pedreira");
    mvwprintw(win, 11, 2, "Rodrigo Macedo    Dário Guimarães");
}

void desenhaBoxTitulo(WINDOW *win, int ncols)
{
    box(win, 0, 0);
    mvwprintw(win, 0, (ncols / 2) - 4, " TriviaLike "); // nome do menu
}

void desenhaEcraDefault(WINDOW *win, int nrows, int ncols, Menu menus[], char key)
{
    limpaEcra(win, nrows, ncols);
    desenhaBoxTitulo(win, ncols);
    desenhaEventos(win, menus, 4, COLOR_WHITE, key);
}

void desenhaMenuInicial(WINDOW *win, State *state)
{
    UNUSED(win);
    UNUSED(state);

    int nrows, ncols;
    getmaxyx(stdscr, nrows, ncols);

    int y = (nrows / 2) - 4;
    int x = (ncols / 2) - 2;

    box(win, 0, 0); // desenhar caixa

    wattron(win, COLOR_PAIR(COLOR_WHITE) | A_BOLD); //  cor da caixa

    mvwprintw(win, 0, (ncols / 2) - 4, " TriviaLike "); // nome do menu

    wattroff(win, COLOR_PAIR(COLOR_WHITE) | A_BOLD); // desativar cor da caixa ???

    Menu menus[4] =
        {
            {"1.Jogar", y, x, '1'},
            {"2.Opcoes", y + 3, x, '2'},
            {"3.Sobre", y + 6, x, '3'},
            {"4.Sair", y + 9, x, '4'},
        };

    // MenuBar/Menu: inicialização
    wattron(win, COLOR_PAIR(COLOR_WHITE));
    desenhaInicializacao(win, menus, 4);
    wattroff(win, COLOR_PAIR(COLOR_WHITE));

}

/*

      // Menu: reage a inputs do user para acionar triggers (que selecionam opções)
        switch (ch)
        {
        case '1':
        // MenuBar: seleciona menu x
            wattron (win, COLOR_PAIR(3) | A_STANDOUT);
            mvwprintw(win, y, x, "1.Jogar");
            wattroff (win, COLOR_PAIR(3) | A_STANDOUT);

            mvwprintw(win, y+3, x, "2.Options");
            mvwprintw(win, y+6, x, "3.Sobre");
            mvwprintw(win, y+9, x, "4.Sair");
            break;

        case '2':
        // MenuBar: seleciona menu x
            wattron (win, COLOR_PAIR(3) | A_STANDOUT);
            mvwprintw(win, y+3, x, "2.Options");
            wattroff (win, COLOR_PAIR(3) | A_STANDOUT);

            mvwprintw(win, y, x, "1.Jogar");
            mvwprintw(win, y+6, x, "3.Sobre");
            mvwprintw(win, y+9, x, "4.Sair");
            break;

        case '3':
        // MenuBar: seleciona menu x
            wattron (win, COLOR_PAIR(3) | A_STANDOUT);
            mvwprintw(win, y+6, x, "3.Sobre");
            wattroff (win, COLOR_PAIR(3) | A_STANDOUT);

            mvwprintw(win, y, x, "1.Jogar");
            mvwprintw(win, y+3, x, "2.Options");
            mvwprintw(win, y+9, x, "4.Sair");
            break;

        case '4':
        // MenuBar: seleciona menu x
            wattron (win, COLOR_PAIR(3) | A_STANDOUT);
            mvwprintw(win, y+9, x, "4.Deseja sair (s/n)");
            wattroff (win, COLOR_PAIR(3) | A_STANDOUT);

            mvwprintw(win, y, x, "1.Jogar");
            mvwprintw(win, y+3, x, "2.Options");
            mvwprintw(win, y+6, x, "3.Sobre");

                while (ch = wgetch(win))
                {
                 switch (ch)
                 {
                    case 's':
                      sair = 1;
                      break;

                    default:
                    mvwprintw(win, y+9, x, "                     ");
                    break;
                 }

                clear;
                wrefresh;
                break;

                }

        default:
        // MenuBAr: reset dos menus
            mvwprintw(win, y, x, "1.Jogar");
            mvwprintw(win, y+3, x, "2.Options");
            mvwprintw(win, y+6, x, "3.Sobre");
            mvwprintw(win, y+9, x, "4.Sair");
            break;
        }

        if (sair == 1) break;
     */

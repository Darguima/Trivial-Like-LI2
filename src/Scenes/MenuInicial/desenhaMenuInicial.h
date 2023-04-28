#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <string.h>
#include <menu.h>
#include "../../state.h"

//void desenhaMenuInicial(WINDOW* window, State* state);

typedef struct MenuStruct
{
    char texto[100]; // texto do menu
    int y_inicial; // o menu começa na posição y
    int x_inicial; // o menu começa na posição x
    char trigger; // tecla que dá trigger à ação

}Menu;

/*typedef struct MenuBarStruct
{
    WINDOW *win; // janela
    Menu *menus; // array de menus
    int n_menus; // número de menus
}MenuBar; */



void desenhaInicializacao (WINDOW *win, Menu menus[],int n_menus)
{
    for (int i = 0; i < n_menus; i++)
    {
       mvwprintw (win, menus[i].y_inicial, menus[i].x_inicial, "%s" ,menus[i].texto); 
    }   
}

void limpaEcra (WINDOW *win, int y, int x)
{
    for (size_t i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            mvwprintw (win,i, j, " ");
        }        
    }
    box(win, 0,0);
    
}


int desenhaEventos (WINDOW *win, Menu menus[], int n_menus, int cor, char key)
{
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // cor da caixa
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // cor do fundo da janela
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // cor das opções

    int menu_atual= -1;
    int sair = -1;

    for (int i = 0; i < n_menus; i++)
    {
        if (key == menus[i].trigger)
        {
            wattron (win, COLOR_PAIR(cor) | A_STANDOUT);
            mvwprintw(win, menus[i].y_inicial, menus[i].x_inicial, "%s", menus[i].texto);
            wattroff (win, COLOR_PAIR(cor) | A_STANDOUT);
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
            wattron (win, COLOR_PAIR(cor) | A_STANDOUT);
            mvwprintw(win, (menus[n_menus-1].y_inicial)+2, (menus[n_menus-1].x_inicial)-6, "Deseja Sair? (s/n) ");
            wattroff (win, COLOR_PAIR(cor) | A_STANDOUT);
    }
    
}

void desenhaSobre(WINDOW *win, int y, int x)
{
    mvwprintw (win, y, 1, " Pressione ESC para voltar atrás ");
    mvwprintw (win, 2, 2, "TriviaLike é um jogo criado com base no 'Rogue',");
    mvwprintw (win, 3, 2, "um jogo lançado em 1980 que deu origem a todo um");
    mvwprintw (win, 4, 2, "género, que se subdivide em rogue-like e lite.");
    mvwprintw (win, 6, 2, "Este é um jogo criado por um grupo de colegas");
    mvwprintw (win, 7, 2, "universitários, com o fim de realizar um projeto");
    mvwprintw (win, 8, 2, "em C.");
    mvwprintw (win, 10, 2, "Hugo Rauber       Afonso Pedreira");
    mvwprintw (win, 11, 2,"Rodrigo Macedo    Dário Guimarães");
}

void desenhaBoxTitulo (WINDOW *win, int ncols)
{
    box (win, 0,0);
    mvwprintw(win, 0, (ncols/4)-5, " TriviaLike "); // nome do menu
}

void desenhaEcraDefault (WINDOW *win,int nrows, int ncols, Menu menus[], int n_menus, int cor, char key) 
{
     limpaEcra(win,nrows, ncols);
      desenhaBoxTitulo (win, ncols);
      desenhaEventos (win, menus, 4, 3 , key);
      
}

void desenhaJogador (WINDOW *win, int y, int x, char key)
{
    mvwprintw (win, y,x, "#");
    while (key = wgetch(win))
    {
        switch (key)
        {
        case 'w':
            mvwprintw (win, y-1 ,x, "#");
            break;
        case 'a':
            mvwprintw (win, y ,x-1, "#");
            break;
        case 's':
            mvwprintw (win, y+1, x, "#");
            break;
        case 'd':
            mvwprintw (win, y ,x+1, "#");
            break;
        
        default:
            break;
        }
    }
    
    
}



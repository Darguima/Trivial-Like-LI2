#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "eventosMenuInicial.h"
#include "desenhaMenuInicial.h"
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



int main()
{
    initscr(); // iniciar ecra
    noecho();  // nao mostra no ecra o que o user escreve
    cbreak(); // permite a leitura de teclas especiais, incluindo Esc
    keypad(stdscr, TRUE); // ativa a leitura das teclas especiais como o Esc
    curs_set(0); //desativa o rato


    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // cor da caixa
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // cor do fundo da janela
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // cor das opções

    int nrows, ncols;
    getmaxyx(stdscr, nrows, ncols);
    
    int y = (nrows/4) -5;
    int x = (ncols/4) - 3;


    WINDOW *win = newwin(nrows / 2, ncols / 2, nrows / 4, ncols / 4);

    wbkgd(win, COLOR_PAIR(2)); // definir cor de fundo da janela

    box(win, 0, 0); // desenhar caixa

    wattron(win, COLOR_PAIR(1) | A_BOLD); //  cor da caixa

    mvwprintw(win, 0, (ncols/4)-5, " TriviaLike "); // nome do menu

    wattroff(win, COLOR_PAIR(1) | A_BOLD); // desativar cor da caixa ???
  
    Menu menus[4] =
    {
      {"1.Jogar",y ,x,'1'},
      {"2.Opcoes",y+3 , x,'2'},
      {"3.Sobre",  y+6,x,'3'},
      {"4.Sair", y+9,x,'4'},
    };  
      
    // MenuBar/Menu: inicialização
    wattron(win, COLOR_PAIR (3));
    desenhaInicializacao (win,menus,4);
    wattroff(win, COLOR_PAIR(3));

    char key;
    int sair=0;

    while (key = wgetch(win))
    {
      switch (key)
      {
     /* case '1':
      limpaEcra(win, nrows, ncols);
      desenhaBoxTitulo(win, ncols);

      while (key = wgetch(win))
      {
        if (key == 27)
        {
          break;
        }
        
        if (key == 'w' || key == 'a' || key == 's' || key == 'd')
        {
        desenhaJogador (win, 0,0, key);
        }
      }
      
      


      break;*/
      case '4':
      desenhaEventos (win, menus, 4, 3 , key);

      while (key = wgetch(win))
      {
        
        if (key == 's')
        {
          sair = 1;
          break;
        }
        else
        if (key == 'n')
        {
        limpaEcra(win, nrows, ncols);
        desenhaInicializacao (win, menus,4);
        desenhaBoxTitulo(win, ncols);
        break;
        }

      }

      break;

      case '3':
      limpaEcra (win, nrows, ncols);
      desenhaSobre (win, 0, 2);
      
      while (key = wgetch(win))
      {
          if (key == 27)
          {
            limpaEcra (win, nrows, ncols);
            desenhaBoxTitulo (win, ncols);
            desenhaInicializacao(win, menus,4);
            wrefresh;
            break;
          }
           
      }
      
      break;

      
      default:
      desenhaEcraDefault (win, nrows, ncols, menus, 4, 3,key);
      break;
    
      }

      if (sair == 1) break;
    }
    
    endwin();
    return 0;
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

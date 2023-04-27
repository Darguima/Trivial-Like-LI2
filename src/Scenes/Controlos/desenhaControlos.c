#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

#define NUM_OPTIONS 5
#define MAX_OPTION_LEN 30

void print_menu(WINDOW *win, char options[][MAX_OPTION_LEN], int num_options, int highlight, int side, int help);

void desenhaControlos(WINDOW* window, State* state) {
  UNUSED(window);
  UNUSED(state);
  mvprintw(1, 28 , "T    R     I     V     I     A     L          L     I     K     E");


  char options[NUM_OPTIONS][MAX_OPTION_LEN] = { "move  up", "move  down", "move  left", "move  right", "leave" };

    // janela para menu
    int startx = (COLS - 30) / 2 -60;
    int starty = 10; 
    WINDOW *menu_win = newwin(30, 150, starty, startx);
    keypad(menu_win, TRUE); // ativar teclas de setas
    refresh();

    print_menu(menu_win, options, NUM_OPTIONS, state->controloMenu.highlight, state->controloMenu.side, state->controloMenu.help);

  
}
void print_menu(WINDOW *win, char options[][MAX_OPTION_LEN], int num_options, int highlight, int side, int help) {
    int x, y, z, i;
    box(win, 0, 0); // draw border
    if(side==0){
    for (i = 0; i < num_options; i++) {
        z = 2 * i + 1;
        y = i + 1;
        x = 2;
        if (highlight == y) {
            wattron(win, A_REVERSE); // highlight current option
        }
        mvwaddstr(win, z, x, options[i]);
        if (highlight == y) {
            wattroff(win, A_REVERSE); // turn off highlight
        }
        
    }
    }
    //botao help para side 1
    mvwaddstr(win, 1, 130, "help");
    if(side==1){
        for (i = 0; i < num_options; i++) { // imprimir opcoes outra vez para remover highlight para quando side é 1
        z = 2 * i + 1;
        y = i + 1;
        x = 2;
        mvwaddstr(win, z, x, options[i]);
    }
    wattron(win, A_REVERSE);
    mvwaddstr(win, 1, 130, "help");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 28, 76, " ");
    }

    

    // print arrow or 'q' based on selection
    if(side==0){
    switch (highlight) {
    case 1:
        mvwprintw(win, 20, 2, "->    up arrow   <-");
        mvwprintw(win, 10, 75, "  .   ");
        mvwprintw(win, 11, 75, " ...  ");
        mvwprintw(win, 12, 75, "..... ");
        mvwprintw(win, 13, 75, "  .   ");
        mvwprintw(win, 14, 75, "  .   ");
        mvwprintw(win, 15, 75, "  .   ");
        mvwprintw(win, 28, 76, " "); //por entrada de texto num sitio porreiro
        

        break;
    case 2:
        mvwprintw(win, 20, 2, "->   down arrow  <-");
        mvwprintw(win, 10, 75, "  .   ");
        mvwprintw(win, 11, 75, "  .   ");
        mvwprintw(win, 12, 75, "  .   ");
        mvwprintw(win, 13, 75, "..... ");
        mvwprintw(win, 14, 75, " ...  ");
        mvwprintw(win, 15, 75, "  .   ");
        mvwprintw(win, 28, 76, " ");
        break;
    case 3:
        mvwprintw(win, 20, 2, "->   left arrow  <-");
        mvwprintw(win, 10, 75, "      ");
        mvwprintw(win, 11, 75, "   .  ");
        mvwprintw(win, 12, 75, "   .. ");
        mvwprintw(win, 13, 75, "......");
        mvwprintw(win, 14, 75, "   .. ");
        mvwprintw(win, 15, 75, "   . ");
        mvwprintw(win, 28, 76, " ");
        break;
    case 4:
        mvwprintw(win, 20, 2, "->  right arrow  <-");
        mvwprintw(win, 10, 75, "      ");
        mvwprintw(win, 11, 75, "  .   ");
        mvwprintw(win, 12, 75, " ..   ");
        mvwprintw(win, 13, 75, "......");
        mvwprintw(win, 14, 75, " ..   ");
        mvwprintw(win, 15, 75, "  .   ");
        mvwprintw(win, 28, 76, " ");
        break;
    case 5:
        mvwprintw(win, 20, 2, "->    press q    <-");
        mvwprintw(win, 10, 75, "......");
        mvwprintw(win, 11, 75, ".    .");
        mvwprintw(win, 12, 75, "......");
        mvwprintw(win, 13, 75, "     .");
        mvwprintw(win, 14, 75, "     .");
        mvwprintw(win, 15, 75, "     .");
        mvwprintw(win, 28, 76, " ");
        break;
    default:
        break;
    }
    }
    if (help==1)
    {
        mvwprintw(win, 25, 76, "$money$");   
        mvwprintw(win, 28, 76, " ");
    }
    if(help==0){
        mvwprintw(win, 25, 76, "       ");
        mvwprintw(win, 28, 76, " ");
    }
    
    
    wrefresh(win); // refresh window
}

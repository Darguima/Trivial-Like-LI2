#include <ncurses.h>

#include "../../state.h"

void desenhaJogo(WINDOW* window, State* state, int nrows, int ncols, int mapa[ncols][nrows]);
void gerarMapa (int ncols , int nrows , int mapa [ncols][nrows]);
void applycelular ( int x , int y , int mapa [x][y]);
void povoarmapa57 (int linhas , int colunas ,int arroz[linhas][colunas]);


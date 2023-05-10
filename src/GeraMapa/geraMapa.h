#include <ncurses.h>

#include "../state.h"

int isOk(int x, int y, int xmax, int ymax);
int is_pos_free(Mapa mapa, int x, int y);
void geraMapa(State *state, int ncols, int nrows);

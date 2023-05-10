#include <ncurses.h>

#include "../../state.h"

void eventosJogo(State *state);
void save_game_state(const char *filename, int vida, const char *username, int numMapaAtual, int dinheiro);

#include <ncurses.h>
#include <json-c/json.h>
#include "../state.h"

void save_game_state(const char *filename, int vida, const char *username, int numMapaAtual, int dinheiro, int armaPrincipal, int armaSecundaria);
void load_game_state(const char *filename, State *state);
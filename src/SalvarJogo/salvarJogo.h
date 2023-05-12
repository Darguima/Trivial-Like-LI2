#include "../state.h"

void save_game_state(const char *filename, int vida, const char *username, int numMapaAtual, int dinheiro, int armaPrincipalIndex, int armaSecundariaIndex);
void load_game_state(const char *filename, State *state);
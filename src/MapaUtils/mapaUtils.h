#include "../state.h"

int esta_sobre_arma(State *state, ArmaNoMapa **armaSobreposta);
int esta_sobre_objeto(State *state, ObjetoNoMapa **ObjetoSobreposto);
int esta_sobre_mob(State *state, MobNoMapa **mobSobreposto);
int estaDentroDoMapa(int x, int y, int xmax, int ymax);
int estaSemParede(Mapa mapa, int x, int y);
int estaTotalmenteLivreParaOUser(State *state, int x, int y);
int estaTotalmenteLivre(State *state, int x, int y);
int distancia (Coordenadas player, Coordenadas mob);

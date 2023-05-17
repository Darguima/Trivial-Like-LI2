#include "../state.h"

<<<<<<< HEAD
=======
ElementosDoMapa** alocar_matrix_mapa(int matrix_width, int matrix_height);
void libertar_matrix_mapa(ElementosDoMapa** matrix, int matrix_width);

>>>>>>> eed931ca12c1ac2b107966dc10c7cde5e43994cb
int esta_sobre_arma(State *state, ArmaNoMapa **armaSobreposta);
int esta_sobre_objeto(State *state, ObjetoNoMapa **ObjetoSobreposto);
int esta_sobre_mob(State *state, MobNoMapa **mobSobreposto);

int estaDentroDoMapa(int x, int y, int xmax, int ymax);
int estaSemParede(Mapa mapa, int x, int y);
int estaTotalmenteLivreParaOUser(State *state, int x, int y);
int estaTotalmenteLivre(State *state, int x, int y);

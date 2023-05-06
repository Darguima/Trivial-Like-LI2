#include "../../state.h"

void atualizar_moedas(State *state, int pos_x, int pos_y) {
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa != Moeda) return;

  state->mapa.matrix[pos_x][pos_y] = Vazio;
  state->jogoAtual.jogador.dinheiro++;
}

void atualizar_mapa(State *state){
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  atualizar_moedas(state, pos_x, pos_y);
}

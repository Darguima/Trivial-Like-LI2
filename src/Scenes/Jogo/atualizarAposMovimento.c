#include "../../state.h"

void atualizarMoedas(State *state, int pos_x, int pos_y) {
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa != Moeda) return;

  state->jogoAtual.mensagem_descricao = "Parabéns, encontraste uma moeda!!";
	state->jogoAtual.mensagem_controlos = "A moeda é automaticamente recolhida";

  state->mapa.matrix[pos_x][pos_y] = Vazio;
  state->jogoAtual.jogador.dinheiro++;
}

int esta_sobre_arma(State *state, ArmaNoMapa **armaSobreposta) {
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int arma_i = 0; arma_i < armasNoMapaLength; arma_i++)
  {
    if (state->jogoAtual.armas[arma_i].posicao.x == pos_x && state->jogoAtual.armas[arma_i].posicao.y == pos_y) {
      *armaSobreposta = &(state->jogoAtual.armas[arma_i]);
      return 1;
    }
  }

  return 0;
}

void atualizarArmas(State *state) {
  ArmaNoMapa *armaSobreposta;
  if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->available) {
    state->jogoAtual.mensagem_descricao = armaSobreposta->arma.mensagem;
    state->jogoAtual.mensagem_controlos = "Pressiona 'p' para pegar";
  }
}

int esta_sobre_mob(State *state, MobNoMapa **mobSobreposto) {
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
  {
    if (state->jogoAtual.mobs[mob_i].posicao.x == pos_x && state->jogoAtual.mobs[mob_i].posicao.y == pos_y) {
      *mobSobreposto = &(state->jogoAtual.mobs[mob_i]);
      return 1;
    }
  }

  return 0;
}

void atualizarMobs(State *state) {
  MobNoMapa *mobSobreposto;
  if (esta_sobre_mob(state, &mobSobreposto) && mobSobreposto->mob.vida > 0) {
    state->jogoAtual.mensagem_descricao = "A lutar com um mob";
    state->jogoAtual.mensagem_controlos = "Pressiona 'por enquanto nada :)' para lutar. PEace";
  }
}

void atualizarAposMovimento(State *state){
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  state->jogoAtual.mensagem_descricao = "Procura a Porta!!";
	state->jogoAtual.mensagem_controlos = "Usa as setas para te moveres";

  atualizarMoedas(state, pos_x, pos_y);
  atualizarArmas(state);
  atualizarMobs(state);
}

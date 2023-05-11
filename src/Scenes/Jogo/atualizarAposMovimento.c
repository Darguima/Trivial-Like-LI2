#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"

void atualizarMoedas(State *state, int pos_x, int pos_y)
{
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa != Moeda)
    return;

  state->jogoAtual.mensagem_descricao = "Encontraste uma moeda!";
  state->jogoAtual.mensagem_controlos = "A moeda é automaticamente recolhida";

  state->mapa.matrix[pos_x][pos_y] = Vazio;
  state->jogoAtual.jogador.dinheiro++;
}

int esta_sobre_arma(State *state, ArmaNoMapa **armaSobreposta)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int arma_i = 0; arma_i < armasNoMapaLength; arma_i++)
  {
    if (state->jogoAtual.armas[arma_i].posicao.x == pos_x && state->jogoAtual.armas[arma_i].posicao.y == pos_y)
    {
      *armaSobreposta = &(state->jogoAtual.armas[arma_i]);
      return 1;
    }
  }

  return 0;
}

void atualizarArmas(State *state)
{
  ArmaNoMapa *armaSobreposta;
  if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
  {
    state->jogoAtual.mensagem_descricao = armaSobreposta->arma.mensagem;
    state->jogoAtual.mensagem_controlos = "Pressiona [Z] para usar como primária, [X] como secundária.";
  }
}



int esta_sobre_mob(State *state, MobNoMapa **mobSobreposto)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
  {
    if (state->jogoAtual.mobs[mob_i].posicao.x == pos_x && state->jogoAtual.mobs[mob_i].posicao.y == pos_y)
    {
      *mobSobreposto = &(state->jogoAtual.mobs[mob_i]);
      return 1;
    }
  }

  return 0;
}

void moverMobs(State *state)
{
  for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
  {
    int *pos_x = &(state->jogoAtual.mobs[mob_i].posicao.x);
    int *pos_y = &(state->jogoAtual.mobs[mob_i].posicao.y);

    int x_deslocamento, y_deslocamento;

    x_deslocamento = 1, y_deslocamento = 1;

    if (is_pos_free(state->mapa, *pos_x + x_deslocamento, *pos_y + y_deslocamento))
    {
      *pos_x += x_deslocamento;
      *pos_y += y_deslocamento;
    }
  }
}

void atualizarMobs(State *state)
{
  moverMobs(state);

  MobNoMapa *mobSobreposto;
  if (esta_sobre_mob(state, &mobSobreposto) && mobSobreposto->mob.vida > 0)
  {
    state->jogoAtual.mensagem_descricao = "Em combate!";
    state->jogoAtual.mensagem_controlos = "Pressiona [Z] para atacar com a primária, [X] com a secundária.";

    // Atualiza a informação dos mobs
    state->jogoAtual.mensagem_nomeMob = mobSobreposto->mob.nome;
    state->jogoAtual.mensagem_vidaMob = mobSobreposto->mob.vida; //! aqui ocorre o erro de conversão

  }
}

void atualizarAposMovimento(State *state)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  state->jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
  state->jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";
  state->jogoAtual.mensagem_nomeMob = "";
  state->jogoAtual.mensagem_vidaMob = "";

  atualizarMoedas(state, pos_x, pos_y);
  atualizarArmas(state);
  atualizarMobs(state);
}

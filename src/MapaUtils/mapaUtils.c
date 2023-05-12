#include "../state.h"

int esta_sobre_mob(State *state, MobNoMapa **mobSobreposto)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
  {
    if (
        state->jogoAtual.mobs[mob_i].posicao.x == pos_x &&
        state->jogoAtual.mobs[mob_i].posicao.y == pos_y &&
        state->jogoAtual.mobs[mob_i].mob.vida > 0)
    {
      *mobSobreposto = &(state->jogoAtual.mobs[mob_i]);
      return 1;
    }
  }

  return 0;
}

int esta_sobre_arma(State *state, ArmaNoMapa **armaSobreposta)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  for (int arma_i = 0; arma_i < armasNoMapaLength; arma_i++)
  {
    if (
        state->jogoAtual.armas[arma_i].posicao.x == pos_x &&
        state->jogoAtual.armas[arma_i].posicao.y == pos_y &&
        state->jogoAtual.armas[arma_i].disponivel)
    {
      *armaSobreposta = &(state->jogoAtual.armas[arma_i]);
      return 1;
    }
  }

  return 0;
}

int estaDentroDoMapa(int x, int y, int xmax, int ymax)
{
  if (x >= 0 && x < xmax && y >= 0 && y < ymax)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int estaSemParede(Mapa mapa, int x, int y)
{
  return estaDentroDoMapa(x, y, mapa.width, mapa.height) && mapa.matrix[x][y].tipo != Parede;
}

// O user pode entrar nesta posição e não vai estar a sobrepor nada
int estaTotalmenteLivreParaOUser(State *state, int x, int y)
{
  int *null = 0;

  return estaDentroDoMapa(x, y, state->mapa.width, state->mapa.height) &&
         state->mapa.matrix[x][y].tipo == Vazio &&
         !esta_sobre_arma(state, (ArmaNoMapa **) &null) &&
         !esta_sobre_mob(state, (MobNoMapa **) &null);
}

// Não existe mesmo nada nesta posição, nem se quer o user
int estaTotalmenteLivre(State *state, int x, int y)
{
  return estaTotalmenteLivreParaOUser(state, x, y) &&
         state->jogoAtual.jogador.posicao.x != x &&
         state->jogoAtual.jogador.posicao.y != y;
}

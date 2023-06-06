#include <stdlib.h>
#include "./eventosJogo.h"
#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"
#include "../../MapaUtils/mapaUtils.h"
#include "../../SalvarJogo/salvarJogo.h"

void atualizarPortais(State *state, int pos_x, int pos_y)
{
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa.tipo != PortaProximoMapa)
    return;

  state->jogoAtual.jogador.numMapaAtual++;

  geraMapa(state);

  save_game_state(state);
}

void atualizarMoedas(State *state, int pos_x, int pos_y)
{
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa.tipo != Moeda)
    return;

  state->jogoAtual.mensagem_descricao = "Encontraste uma moeda!";
  state->jogoAtual.mensagem_controlos = "A moeda foi automaticamente recolhida";

  state->mapa.matrix[pos_x][pos_y].tipo = Vazio;
  state->jogoAtual.jogador.dinheiro++;
}

void atualizarArmas(State *state)
{
  ArmaNoMapa *armaSobreposta;
  if (esta_sobre_arma(state, &armaSobreposta))
  {
    state->jogoAtual.mensagem_descricao = armaSobreposta->arma.mensagem;
    state->jogoAtual.mensagem_controlos = "Pressiona [Z] para usar como primaria, [X] como secundaria.";
  }
}

void atualizarObjetos(State *state)
{
  ObjetoNoMapa *objetoSobreposto;
  if (esta_sobre_objeto(state, &objetoSobreposto))
  {
    state->jogoAtual.mensagem_descricao = objetoSobreposto->objeto.mensagem;
    state->jogoAtual.mensagem_controlos = "Encontraste um objeto! Pressiona [E] para pegar nele.";
  }
}

void moverMobs(State *state)
{
  for (int mob_i = 0; mob_i < state->mapa.qntMobsNoMapaLength; mob_i++)
  {
    int *pos_x = &(state->jogoAtual.mobs[mob_i].posicao.x);
    int *pos_y = &(state->jogoAtual.mobs[mob_i].posicao.y);
    int x_Aux = *pos_x;
    int y_Aux = *pos_y;
    int aux_Dist;
    int min_Dist;
    int nao_perseguicao = rand() % 100;

    if ((min_Dist = distancia(state->jogoAtual.jogador.posicao, state->jogoAtual.mobs[mob_i].posicao)) > state->jogoAtual.mobs[mob_i].mob.raioVisao || nao_perseguicao<20)
    {
      int x_deslocamento, y_deslocamento;

      x_deslocamento = (rand() % 3) - 1;
      y_deslocamento = (rand() % 3) - 1;

      if (estaTotalmenteLivre(state, *pos_x + x_deslocamento, *pos_y + y_deslocamento))
      {
        *pos_x += x_deslocamento;
        *pos_y += y_deslocamento;
      }
      continue;
    }
    if (min_Dist <= 1)
    {
      state->jogoAtual.mobs[mob_i].posicao = state->jogoAtual.jogador.posicao;
      continue;
    }
    
    for (int x_pos = -1 ; x_pos<=1 ; x_pos++) {
      for(int y_pos = -1 ; y_pos <=1 ; y_pos++) {
        Coordenadas mob_Temp = {x_Aux+ x_pos, y_Aux + y_pos};
        if((x_pos==0 && y_pos != 0)  || (x_pos !=0 && y_pos==0)) {
           if (estaSemParede(state->mapa,mob_Temp.x,mob_Temp.y ))
        {
          if ((aux_Dist = distancia(state->jogoAtual.jogador.posicao, mob_Temp)) < min_Dist)
          {
            min_Dist = aux_Dist;
            state->jogoAtual.mobs[mob_i].posicao = mob_Temp;
          }
        }
      }
        else{
           if (estaSemParede(state->mapa, mob_Temp.x, mob_Temp.y) && estaSemParede(state->mapa, x_Aux +x_pos, *pos_y) && estaSemParede(state->mapa, *pos_x, y_Aux + y_pos))
    {
      if ((aux_Dist = distancia(state->jogoAtual.jogador.posicao, mob_Temp)) < min_Dist)
      {
        min_Dist = aux_Dist;
        state->jogoAtual.mobs[mob_i].posicao = mob_Temp;
      }
    }
            

        }
      }
    }
  }
}

void atacarComMobs(State *state)
{
  Coordenadas player_pos = state->jogoAtual.jogador.posicao;

  for (int mob_i = 0; mob_i < state->mapa.qntMobsNoMapaLength; mob_i++)
  {
    MobNoMapa mobAtual = state->jogoAtual.mobs[mob_i];
    if (mobAtual.mob.vida <= 0)
    {
      continue;
    }

    // Monstros atacam na vertical e horizontal e no sítio
    if (
        (mobAtual.posicao.x == player_pos.x && mobAtual.posicao.y == player_pos.y))
    {
      if (ataqueComProbabilidade(mobAtual.mob.arma, &(state->jogoAtual.jogador.vida)))
      {
        state->jogoAtual.mensagem_descricao = "Estas a ser atacado!";
        state->jogoAtual.mensagem_controlos = "Foge ou contra-ataca.";
      }

      reageVida(state);
    }
  }
}

void atualizarMobs(State *state)
{
  moverMobs(state);
  atacarComMobs(state);

  MobNoMapa *mobSobreposto;
  if (esta_sobre_mob(state, &mobSobreposto))
  {
    state->jogoAtual.mensagem_descricao = "Em combate!";
    state->jogoAtual.mensagem_controlos = "Pressiona [Z] para atacar com a primaria, [X] com a secundaria.";
  }
}

void atualizarAposMovimento(State *state)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  state->jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
  state->jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";
  state->jogoAtual.mensagem_inventario = "Este e o teu inventario!";
  state->jogoAtual.mensagem_inventario_controlos = "Usa os numeros para escolher um objeto.";

  /*
   * A ordem pela qual aparecem as seguintes funções tem relevância no resultado final das alterações.
   * Quanto mais para o fim estiver a função, maior prioridade têm as suas alterações, sobrescrevendo
   * o que pode ter sido feito pelas outras (p.e. as mensagens de descrição e controlos)
   */

  atualizarPortais(state, pos_x, pos_y);
  atualizarMoedas(state, pos_x, pos_y);
  atualizarArmas(state);
  atualizarObjetos(state);
  atualizarMobs(state);
}

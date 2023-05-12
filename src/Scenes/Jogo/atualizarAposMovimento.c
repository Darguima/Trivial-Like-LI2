#include <stdlib.h>
#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"
#include "../../MapaUtils/mapaUtils.h"

void atualizarMoedas(State *state, int pos_x, int pos_y)
{
  ElementosDoMapa elementoMapa = state->mapa.matrix[pos_x][pos_y];

  if (elementoMapa.tipo != Moeda)
    return;

  state->jogoAtual.mensagem_descricao = "Encontraste uma moeda!";
  state->jogoAtual.mensagem_controlos = "A moeda é automaticamente recolhida";

  state->mapa.matrix[pos_x][pos_y].tipo = Vazio;
  state->jogoAtual.jogador.dinheiro++;
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

void moverMobs(State *state)
{
  for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
  {
    int *pos_x = &(state->jogoAtual.mobs[mob_i].posicao.x);
    int *pos_y = &(state->jogoAtual.mobs[mob_i].posicao.y);

    int x_deslocamento, y_deslocamento;

    x_deslocamento = (rand() % 3) - 1;
    y_deslocamento = (rand() % 3) - 1;

    if (estaTotalmenteLivre(state, *pos_x + x_deslocamento, *pos_y + y_deslocamento))
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
  }
}

void atualizarAposMovimento(State *state)
{
  int pos_x = state->jogoAtual.jogador.posicao.x;
  int pos_y = state->jogoAtual.jogador.posicao.y;

  state->jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
  state->jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";

  /*
	* A ordem pela qual aparecem as seguintes funções tem relevância no resultado final das alterações.
	* Quanto mais para o fim estiver a função, maior prioridade têm as suas alterações, sobrescrevendo
  * o que pode ter sido feito pelas outras (p.e. as mensagens de descrição e controlos) 
	*/
  atualizarMoedas(state, pos_x, pos_y);
  atualizarArmas(state);
  atualizarMobs(state);
}

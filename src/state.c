#include <stdlib.h>
#include "state.h"

State criarEstado() {
	State state;

  state.sceneAtual = MenuInicial;
	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = NULL;
	state.jogoAtual.jogador.posicao.x = 0;
	state.jogoAtual.jogador.posicao.y = 0;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.mensagem = NULL;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = Nada;
	state.jogoAtual.jogador.armaSecundaria = Nada;
	state.jogoAtual.Mapa  = NULL;

  return state;
}
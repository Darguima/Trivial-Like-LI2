#include "state.h"

State criarEstado() {
	State state;

  state.sceneAtual = MenuInicial;
	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = "";
	state.jogoAtual.jogador.posicao.x = 20;
	state.jogoAtual.jogador.posicao.y = 20;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.mensagem = "";
	state.jogoAtual.jogador.inventario /* = [] */;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = Nada;
	state.jogoAtual.jogador.armaSecundaria = Nada;
	state.jogoAtual.Mapa /* = [] */;

  return state;
}
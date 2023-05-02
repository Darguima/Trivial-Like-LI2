#include <stdlib.h>
#include "state.h"

State criarEstado(int colunas, int linhas) {
	State state;
	int **matrix;
 
    // Allocate memory for the matrix
    matrix = (int **)malloc(colunas * sizeof(int *));
    for (int  i = 0; i < colunas; i++) {
        matrix[i] = (int *)malloc(linhas * sizeof(int));
    }
 
    // Fill the matrix with values

  state.sceneAtual = MenuInicial;
	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = NULL;
	state.jogoAtual.jogador.posicao.x = 3;
	state.jogoAtual.jogador.posicao.y = 3;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.mensagem = NULL;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = Nada;
	state.jogoAtual.jogador.armaSecundaria = Nada;
	state.jogoAtual.Mapa  = NULL;
	state.mapa.width = colunas;
	state.mapa.height = linhas;
	state.mapa.matrix = matrix;


  return state;
}
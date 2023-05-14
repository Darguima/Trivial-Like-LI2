#include <stdlib.h>
#include "state.h"

Arma const punhos = {0, Punhos, "Punhos", 15, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "};
Arma const garras = {1, Garras, "Garras", 10, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."};
Arma const espadaOxidada = {2, EspadaOxidada, "Espada Oxidada", 20, 75, "Espada que pertenceu a um soldado caído em combate."};
Arma const espadaLonga = {3, EspadaLonga, "Espada Longa", 25, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."};
Arma const arco = {4, Arco, "Arco", 40, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."};
Arma const acido = {5, Acido, "Acido", 20, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."};
Arma const cetro = {6, Cetro, "Cetro", 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."};

int const catalogoArmasLength = 7;
Arma const catalogoArmas[] = {punhos, garras, espadaOxidada, espadaLonga, arco, acido, cetro};

Mob const esqueleto1 = {Esqueleto, "Esqueleto", 'E', espadaOxidada, 40, 40, 3};
Mob const esqueleto2 = {Esqueleto, "Esqueleto", 'E', punhos, 40, 40, 3};
Mob const soldadoEsqueleto1 = {SoldadoEsqueleto, "Soldado Esqueleto", 'S', espadaLonga, 60, 60, 4};
Mob const vampiro1 = {Vampiro, "Vampiro", 'V', garras, 70, 70, 8};
Mob const vampiro2 = {Vampiro, "Vampiro", 'V', cetro, 50, 50, 10};
Mob const mutante1 = {Mutante, "Mutante", 'M', punhos, 30, 30, 2};
Mob const mutante2 = {Mutante, "Mutante", 'M', punhos, 10, 10, 2};
Mob const aranha1 = {Aranha, "Aranha", 'A', acido, 30, 30, 10};
Mob const aranha2 = {Aranha, "Aranha", 'A', acido, 40, 40, 8};
Mob const zombie1 = {Zombie, "Zombie", 'Z', garras, 70, 70, 2};

int const catalogoMobsLength = 10;
Mob const catalogoMobs[] = {esqueleto1, esqueleto2, soldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};

State criarEstado(int colunas, int linhas)
{
	State state;

	// Fill the matrix with values

	state.sceneAtual = MenuInicial;

	state.scenesVariables.controlosSceneVars.highlight = 1;
	state.scenesVariables.controlosSceneVars.side = 0;
	state.scenesVariables.controlosSceneVars.help = 0;
	state.scenesVariables.selecionarJogadorSceneVars.delete = 0;
	state.scenesVariables.selecionarJogadorSceneVars.faildelete = 0;
	state.scenesVariables.selecionarJogadorSceneVars.askUser = 0;

	state.mapa.terminal.width = colunas;
	state.mapa.terminal.height = linhas;
	state.mapa.display_width = colunas - 40;
	state.mapa.display_height = linhas - 10;
	state.mapa.matrix_width = 500;
	state.mapa.matrix_height = 500;
	state.mapa.qntArmasNoMapaLength = 0;
	state.mapa.qntMobsNoMapaLength = 0;
	state.mapa.qntMoedasNoMapaLength = 0;
	state.mapa.matrix = (ElementosDoMapa **)malloc(state.mapa.matrix_width * sizeof(ElementosDoMapa *));
	for (int i = 0; i < state.mapa.matrix_width; i++)
		state.mapa.matrix[i] = (ElementosDoMapa *)malloc(state.mapa.matrix_height * sizeof(ElementosDoMapa));

	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = malloc(31);
	state.jogoAtual.jogador.vidaMaxima = 100;
	state.jogoAtual.jogador.posicao.x = 1;
	state.jogoAtual.jogador.posicao.y = 1;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.inventario = NULL; // Alocado depois
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = punhos;
	state.jogoAtual.jogador.armaSecundaria = punhos;
	state.jogoAtual.jogador.numSave = 0;
	state.jogoAtual.mobs = NULL; // Alocado depois
	state.jogoAtual.armas = NULL; // Alocado depois
	state.jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
	state.jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";

	return state;
}

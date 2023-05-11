#include <stdlib.h>
#include "state.h"


const Arma punhos = {Punhos, "Punhos", 7, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos ",0};
const Arma garras = {Garras, "Garras", 20, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh...",1};
const Arma espadaOxidada = {EspadaOxidada, "EspadaOxidada", 25, 75, "Espada que pertenceu a um soldado caído em combate.",2};
const Arma espadaLonga = {EspadaLonga, "EspadaLonga", 30, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador.",3};
const Arma arco = {Arco, "Arco", 45, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão.",4};
const Arma acido = {Acido, "Acido", 40, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca.",5};
const Arma cetro = {Cetro, "Cetro", 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis.",6};

const Arma catalogoArmas[] = {punhos, garras, espadaOxidada, espadaLonga, arco, acido, cetro};
const Mob esqueleto1 = {Esqueleto, espadaOxidada, 50, 3};
const Mob esqueleto2 = {Esqueleto, punhos, 50, 3};
const Mob soldadoEsqueleto1 = {SoldadoEsqueleto, espadaLonga, 70, 4};
const Mob vampiro1 = {Vampiro, garras, 150, 8};
const Mob vampiro2 = {Vampiro, cetro, 60, 10};
const Mob mutante1 = {Mutante, punhos, 40, 2};
const Mob mutante2 = {Mutante, punhos, 20, 2};
const Mob aranha1 = {Aranha, acido, 40, 10};
const Mob aranha2 = {Aranha, acido, 60, 8};
const Mob zombie1 = {Zombie, garras, 100, 2};

const Mob catalogoMobs[] = {esqueleto1, esqueleto2, soldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};

State criarEstado(int colunas, int linhas)
{
	State state;
	int **matrix;

	// Allocate memory for the matrix
	matrix = (int **)malloc(colunas * sizeof(int *));
	for (int i = 0; i < colunas; i++)
	{
		matrix[i] = (int *)malloc(linhas * sizeof(int));
	}

	// Fill the matrix with values

	state.sceneAtual = MenuInicial;

	state.controloMenu.highlight = 1;
	state.controloMenu.side = 0;
	state.controloMenu.help = 0;

	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = "Joao";
	state.jogoAtual.jogador.posicao.x = 3;
	state.jogoAtual.jogador.posicao.y = 3;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.mensagem = NULL;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = punhos;
	state.jogoAtual.jogador.armaSecundaria = punhos;
	state.jogoAtual.jogador.numSave=0;

	state.mapa.width = colunas;
	state.mapa.height = linhas;
	state.mapa.matrix = matrix;

	return state;
}

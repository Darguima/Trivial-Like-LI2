#include <stdlib.h>
#include "state.h"

const Arma punho = {Punhos, 7, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "};
const Arma garras = {Garras, 20, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."};
const Arma espadaOxidada = {EspadaOxidada, 25, 75, "Espada que pertenceu a um soldado caído em combate."};
const Arma espadaLonga = {EspadaLonga, 30, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."};
const Arma arco = {Arco, 45, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."};
const Arma acido = {Acido, 40, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."};
const Arma cetro = {Cetro, 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."};

const Arma catalogoArmas[] = {punho, garras, espadaOxidada, espadaLonga, arco, acido, cetro};

const Mob esqueleto1 = {espadaOxidada, 50, 3};
const Mob esqueleto2 = {punho, 50, 3};
const Mob SoldadoEsqueleto1 = {espadaLonga, 70, 4};
const Mob vampiro1 = {garras, 150, 8};
const Mob vampiro2 = {cetro, 60, 10};
const Mob mutante1 = {punho, 40, 2};
const Mob mutante2 = {punho, 20, 2};
const Mob aranha1 = {acido, 40, 10};
const Mob aranha2 = {acido, 60, 8};
const Mob zombie1 = {garras, 100, 2};

const Mob catalogoMobs[] = {esqueleto1, esqueleto2, SoldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};

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

	// state.armamento = 

	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.username = NULL;
	state.jogoAtual.jogador.posicao.x = 3;
	state.jogoAtual.jogador.posicao.y = 3;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.mensagem = NULL;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = punho;
	state.jogoAtual.jogador.armaSecundaria = punho;

	state.mapa.width = colunas;
	state.mapa.height = linhas;
	state.mapa.matrix = matrix;

	return state;
}

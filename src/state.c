#include <stdlib.h>
#include "state.h"

Arma const punhos = {Punhos, "Punhos", 15, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "};
Arma const garras = {Garras, "Garras", 10, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."};
Arma const espadaOxidada = {EspadaOxidada, "Espada Oxidada", 20, 75, "Espada que pertenceu a um soldado caído em combate."};
Arma const espadaLonga = {EspadaLonga, "Espada Longa", 25, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."};
Arma const arco = {Arco, "Arco", 40, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."};
Arma const acido = {Acido, "Acido", 20, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."};
Arma const cetro = {Cetro, "Cetro", 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."};

int const armasNoMapaLength = 2;
int const catalogoArmasLength = 7;
Arma const catalogoArmas[] = {punhos, garras, espadaOxidada, espadaLonga, arco, acido, cetro};

Mob const esqueleto1 = {Esqueleto, "Esqueleto", espadaOxidada, 40, 3};
Mob const esqueleto2 = {Esqueleto, "Esqueleto", punhos, 40, 3};
Mob const soldadoEsqueleto1 = {SoldadoEsqueleto, "Soldado Esqueleto" ,espadaLonga, 60, 4};
Mob const vampiro1 = {Vampiro, "Vampiro", garras, 70, 8};
Mob const vampiro2 = {Vampiro, "Vampiro", cetro, 50, 10};
Mob const mutante1 = {Mutante, "Mutante", punhos, 30, 2};
Mob const mutante2 = {Mutante, "Mutante", punhos, 10, 2};
Mob const aranha1 = {Aranha, "Aranha", acido, 30, 10};
Mob const aranha2 = {Aranha, "Aranha", acido, 40, 8};
Mob const zombie1 = {Zombie, "Zombie", garras, 70, 2};

int const mobsNoMapaLength = 10;
int const catalogoMobsLength = 10;
Mob const catalogoMobs[] = {esqueleto1, esqueleto2, soldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};

State criarEstado(int colunas, int linhas)
{
	State state;
	ElementosDoMapa **matrix;

	// Allocate memory for the matrix
	matrix = (ElementosDoMapa **)malloc(colunas * sizeof(ElementosDoMapa *));
	for (int i = 0; i < colunas; i++)
	{
		matrix[i] = (ElementosDoMapa *)malloc(linhas * sizeof(ElementosDoMapa));
	}

	// Fill the matrix with values

	state.sceneAtual = MenuInicial;

	state.controloMenu.highlight = 1;
	state.controloMenu.side = 0;
	state.controloMenu.help = 0;

	state.jogoAtual.jogador.vida = 100;
	state.jogoAtual.jogador.vidaMaxima = 100;
	state.jogoAtual.jogador.username = NULL;
	state.jogoAtual.jogador.posicao.x = 3;
	state.jogoAtual.jogador.posicao.y = 3;
	state.jogoAtual.jogador.numMapaAtual = 1;
	state.jogoAtual.jogador.inventario = NULL;
	state.jogoAtual.jogador.dinheiro = 0;
	state.jogoAtual.jogador.armaPrincipal = punhos;
	state.jogoAtual.jogador.armaSecundaria = punhos;

	state.jogoAtual.mobs = malloc(mobsNoMapaLength * sizeof(MobNoMapa));
	state.jogoAtual.armas = malloc(armasNoMapaLength * sizeof(ArmaNoMapa));
	state.jogoAtual.mensagem_descricao = "Encontra a porta para passar de mapa!";
	state.jogoAtual.mensagem_controlos = "Utiliza as setas para te movimentares.";
	state.jogoAtual.mensagem_nomeMob = "";
	state.jogoAtual.mensagem_vidaMob = "";

	state.mapa.terminal.width = colunas;
	state.mapa.terminal.height = linhas;
	state.mapa.width = colunas - 40;
	state.mapa.height = linhas - 10;
	state.mapa.matrix = matrix;

	return state;
}

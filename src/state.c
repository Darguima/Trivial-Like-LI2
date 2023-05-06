#include <stdlib.h>
#include "state.h"

Arma const punhos = {Punhos, "Punhos", 7, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "};
Arma const garras = {Garras, "Garras", 20, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."};
Arma const espadaOxidada = {EspadaOxidada, "EspadaOxidada", 25, 75, "Espada que pertenceu a um soldado caído em combate."};
Arma const espadaLonga = {EspadaLonga, "EspadaLonga", 30, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."};
Arma const arco = {Arco, "Arco", 45, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."};
Arma const acido = {Acido, "Acido", 40, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."};
Arma const cetro = {Cetro, "Cetro", 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."};

int const armasNoMapaLength = 2;
int const catalogoArmasLength = 7;
Arma const catalogoArmas[] = {punhos, garras, espadaOxidada, espadaLonga, arco, acido, cetro};

Mob const esqueleto1 = {Esqueleto, espadaOxidada, 50, 3};
Mob const esqueleto2 = {Esqueleto, punhos, 50, 3};
Mob const soldadoEsqueleto1 = {SoldadoEsqueleto, espadaLonga, 70, 4};
Mob const vampiro1 = {Vampiro, garras, 150, 8};
Mob const vampiro2 = {Vampiro, cetro, 60, 10};
Mob const mutante1 = {Mutante, punhos, 40, 2};
Mob const mutante2 = {Mutante, punhos, 20, 2};
Mob const aranha1 = {Aranha, acido, 40, 10};
Mob const aranha2 = {Aranha, acido, 60, 8};
Mob const zombie1 = {Zombie, garras, 100, 2};

int const mobsNoMapaLength = 10;
int const catalogoMobsLength = 10;
Mob const catalogoMobs[] = {esqueleto1, esqueleto2, soldadoEsqueleto1, vampiro1, vampiro2, mutante1, mutante2, aranha1, aranha2, zombie1};

Objeto const pocaoVidaD       = {PocaoVidaD,"Poção de Vida Definitiva","Recupera toda a vida" }; 
Objeto const pocaoVidaG       = {PocaoVidaG,"Poção de Vida Grande", "Recupera 70 pontos de vida" };
Objeto const pocaoVidaP       = {PocaoVidaP,"Poção de Vida Pequena", "Recupera 40 pontos de vida" };
Objeto const pocaoAumentoVida = {PocaoAumentoVida,"Poção de Aumento de Vida", "Aumenta a vida máxima em 25 pontos" };
Objeto const pocaoMagica      = {PocaoMagica,"Poção Mágica", "Recupera toda a vida e aumenta a vida máxima em 15 pontos" };
Objeto const portalDeBolso    = {PortalDeBolso,"portalDeBolso", "Portal de uma só utilização que muda para o mapa seguinte, amentando a vida máxima em 5 pontos" };

int const objetosNoMapaLength = 2;
int const catalogoObjetosLength = 6;
Objeto const catalogoObjetos[] = {pocaoVidaD, pocaoVidaG,pocaoVidaP,pocaoAumentoVida,pocaoMagica,portalDeBolso,}


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
	state.jogoAtual.mensagem_descricao = "Procura a Porta!!";
	state.jogoAtual.mensagem_controlos = "Usa as setas para te moveres";

	state.mapa.terminal.width = colunas;
	state.mapa.terminal.height = linhas;
	state.mapa.width = colunas - 40;
	state.mapa.height = linhas - 10;
	state.mapa.matrix = matrix;

	return state;
}

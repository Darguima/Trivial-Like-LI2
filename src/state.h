#ifndef ___State_H___
#define ___State_H___




typedef enum scene { /* São as diferentes páginas que podem aparecer ao longo do jogo */
	MenuInicial, /* Primeira página que aparece no jogo */
	SelecionarJogador, // Transição entre Menu Inicial e Jogo (para escolher o jogador)
	Jogo, /* O jogo em si, com o status do jogador, mapa e inventário */
	Controlos,
	Sobre,
	Sair
} Scene;

typedef enum arma { /* Diferentes armas que o player pode ter */
	Nada,
	Espada,
	Arco,
	/* Adicionar mais no futuro */
} Arma;

typedef struct coordenadas {
	int x, y;
} Coordenadas;

typedef struct statusJogador {
	Coordenadas posicao;
	char* username;
	int vida; // valor entre 0 e 100
	Arma armaPrincipal;
	Arma armaSecundaria;
	int dinheiro;
	int numMapaAtual; /* Quantas mapas já foram passados */
	char* mensagem; /* Mensagem para mostrar um texto relevante. ex. qual tecla usar para interagir, algum informação do mapa */
	Arma* inventario;
} StatusJogador;

typedef enum elementosDoMapa {
	Jogador, /* @ */
	Monstros, /* M - com foreground ou background vermelho */
	NPC, /* & */
	Paredes, /* # */
	PortaNormal, /* + - serve para fechar as salas, no futuro se for possível implementar o conceito de chaves escondidas */
	PortaProximoMapa, /* +++|+++|+++ - serve para mudar de mapa */
} ElementosDoMapa;

typedef struct jogoAtual {
	StatusJogador jogador;
	ElementosDoMapa* Mapa;
} JogoAtual;

typedef struct mapa {
	int height;
	int width;
	int** matrix;
}Mapa;

typedef struct state {
	Scene sceneAtual;
	JogoAtual jogoAtual;
	Mapa mapa ;
} State;

State criarEstado(int colunas,int linhas);

#endif

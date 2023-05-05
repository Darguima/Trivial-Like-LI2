#ifndef ___State_H___
#define ___State_H___

typedef enum scene
{										 /* São as diferentes páginas que podem aparecer ao longo do jogo */
	MenuInicial,			 /* Primeira página que aparece no jogo */
	SelecionarJogador, // Transição entre Menu Inicial e Jogo (para escolher o jogador)
	Jogo,							 /* O jogo em si, com o status do jogador, mapa e inventário */
	Controlos,
	Sobre,
	Sair
} Scene;

typedef enum tipoArma { /* Diferentes armas que o player pode ter */
	Punhos,
	Garras,
	EspadaOxidada,
	EspadaLonga,
	Arco,
	Acido,
	Cetro,
	/* Adicionar mais no futuro */
} TipoArma;

typedef struct arma {
    TipoArma tipoarma; // recebe um tipo de arma
    int dano; // dano da arma
    int probA; // isto é a probabilidade de o ataque acertar no objetivo, de 0 a 100
	char* mensagem; // texto que a arma mostra quando se dá inspect no inventário (feature que pode ser implementada ou não)
} Arma;

Arma armas[] = {
	{Punhos , 7, 50, "Um par de punhos que, nas mãos adequadas, fazem grandes estragos "}, // 0
	{Garras, 20, 60, "Garras ensanguentadas que saem das mãos de um grotesco monstro. Urghh..."}, // 1
	{EspadaOxidada,  25, 75, "Espada que pertenceu a um soldado caído em combate."}, // 2
	{EspadaLonga, 30, 95, "Espada forjada pelos melhores ferreiros. Embora não seja muito potente, raramente falha ao seu portador."}, // 3
	{Arco, 45, 30, "Um arco bastante flexível que causa muito dano mas possui uma terrível precisão."}, // 4
	{Acido, 40, 15, "Um líquido lançado por certos monstros que desfaz tudo o que toca."}, // 5
	{Cetro, 15, 100, "Um cetro carregado de magia. O seu baixo dano é compensado com a precisão dos seus projéteis."} // 6
};


typedef struct coordenadas
{
	int x, y;
} Coordenadas;

typedef struct statusJogador
{
	Coordenadas posicao;
	char *username;
	int vida; // valor entre 0 e 100
	Arma armaPrincipal;
	Arma armaSecundaria;
	int dinheiro;
	int numMapaAtual; /* Quantas mapas já foram passados */
	char *mensagem;		/* Mensagem para mostrar um texto relevante. ex. qual tecla usar para interagir, algum informação do mapa */
	Arma *inventario;
} StatusJogador;

typedef enum tipoMob { // o tipo do mob a chamar
	Esqueleto, /* E */
	SoldadoEsqueleto, /* S */
	Vampiro, /* V */ 
	Mutante, /* M */
	Aranha,  /* A */
	Zombie,  /* Z */
	/* Possibilidade de adicionar mais no futuro */
} TipoMob;

typedef struct mob { // podem haver mais que um mob com armas diferentes
	// TipoMob tipomob; // recebe qual o tipo do mob
	Arma arma; // o mob possui uma arma só. Aqui temos de aplicar uma das armas do struct Armas
	int vida; 
	int raioVisao;  // o raio de visão pode variar entre 1 e 10 (provisório). o raio de visão mede-se em quantas 'casas' o mob consegue ver o jogador e começar a atacar 
} Mob;

Mob esqueleto1 = {armas[2], 50, 3};
Mob esqueleto2 = {armas[0], 50, 3};

Mob SoldadoEsqueleto1 = {armas[3], 70, 4};

Mob vampiro1 = {armas[1], 150, 8};
Mob vampiro1 = {armas[6], 60, 10};

Mob mutante1 = {armas[0], 40, 2};
Mob mutante2 = {armas[0], 20, 2};

Mob aranha1 = {armas[5], 40, 10 };
Mob aranha1 = {armas[5], 60, 8 };

Mob zombie1 = {armas[1], 100, 2 };

typedef struct statusMobs {
	Coordenadas posicao;
	Mob mob; // qual o mob e as suas características
} StatusMobs;

typedef enum elementosDoMapa
{
	Jogador,					/* @ */
	Mobs,					/* M - com foreground ou background vermelho */
	NPC,							/* & */
	Paredes,					/* # */
	PortaNormal,			/* + - serve para fechar as salas, no futuro se for possível implementar o conceito de chaves escondidas */
	PortaProximoMapa, /* +++|+++|+++ - serve para mudar de mapa */
} ElementosDoMapa;

typedef struct controlosMenu
{
	int highlight;
	int side;
	int help;
} ControlosMenu;

typedef struct jogoAtual
{
	StatusJogador jogador;
	ElementosDoMapa *Mapa;
} JogoAtual;

typedef struct mapa
{
	int height;
	int width;
	int **matrix;
} Mapa;

typedef struct state
{
	Scene sceneAtual;
	JogoAtual jogoAtual;
	ControlosMenu controloMenu;
	Mapa mapa;
} State;

State criarEstado(int colunas, int linhas);

#endif

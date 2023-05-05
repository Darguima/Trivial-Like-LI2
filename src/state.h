#ifndef ___State_H___
#define ___State_H___

typedef enum scene
{										 /* São as diferentes páginas que podem aparecer ao longo do jogo */
	MenuInicial,			 /* Primeira página que aparece no jogo */
	SelecionarJogador, // Transição entre Menu Inicial e Jogo (para escolher o jogador)
	Jogo,							 /* O jogo em si, com o status do jogador, mapa e inventário */
	Controlos,
	Sobre,
	Sair,
} Scene;

typedef enum armamento /* Diferentes armas que o player e os mobs pode ter */
{
	Punhos,
	Garras,
	EspadaOxidada,
	EspadaLonga,
	Arco,
	Acido,
	Cetro,
} Armamento;

typedef struct arma
{
	Armamento tipoArma;
	int dano;				// dano da arma
	int probA;			// isto é a probabilidade de o ataque acertar no objetivo, de 0 a 100
	char *mensagem; // texto que a arma mostra quando se dá inspect no inventário (feature que pode ser implementada ou não)
} Arma;

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

typedef enum tipoMob
{										// o tipo do mob a chamar
	Esqueleto,				/* E */
	SoldadoEsqueleto, /* S */
	Vampiro,					/* V */
	Mutante,					/* M */
	Aranha,						/* A */
	Zombie,						/* Z */
} TipoMob;

typedef struct mob
{
	Arma arma;
	int vida;
	int raioVisao; // o raio de visão pode variar entre 1 e 10 (provisório). o raio de visão mede-se em quantas 'casas' o mob consegue ver o jogador e começar a atacar
} Mob;

typedef struct statusMobs
{
	Coordenadas posicao;
	Mob mob;
} StatusMobs;

typedef enum elementosDoMapa
{
	Jogador,					/* @ */
	Mobs,							/* M - com foreground ou background vermelho */
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
	
	ControlosMenu controloMenu;
	
	JogoAtual jogoAtual;
	Mapa mapa;
	
} State;

State criarEstado(int colunas, int linhas);

#endif

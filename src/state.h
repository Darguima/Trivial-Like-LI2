#ifndef ___State_H___
#define ___State_H___

/* São as diferentes páginas que podem aparecer ao longo do jogo */
typedef enum scene
{
	MenuInicial,			 /* Primeira página que aparece no jogo */
	SelecionarJogador, /* Transição entre Menu Inicial e Jogo (para escolher o jogador) */
	Jogo,							 /* O jogo em si, com o status do jogador, mapa e inventário */
	Controlos,
	Sobre,
	Sair,
} Scene;

typedef struct coordenadas
{
	int x, y;
} Coordenadas;

typedef struct moeda
{
	int valor; // valor da moeda
	Coordenadas posicao;
} Moeda;

/* Diferentes armas que o player e mobs pode ter */
typedef enum catalogoArmas
{
	Punhos,
	Garras,
	EspadaOxidada,
	EspadaLonga,
	Arco,
	Acido,
	Cetro,
} CatalogoArmas;

typedef struct arma
{
	CatalogoArmas tipoArma;
	char *nome; // nome para ser mostrado no inventário
	int dano;
	int probabilidade; // probabilidade de o ataque acertar no objetivo, de 0 a 1
	char *mensagem;		 // texto que descreve a arma
} Arma;

typedef enum catalogoMobs
{										// o tipo do mob a chamar
	Esqueleto,				/* E */
	SoldadoEsqueleto, /* S */
	Vampiro,					/* V */
	Mutante,					/* M */
	Aranha,						/* A */
	Zombie,						/* Z */
										/* Possibilidade de adicionar mais no futuro */
} CatalogoMobs;

typedef struct mob
{												// podem haver mais que um mob com armas diferentes
	CatalogoMobs tipomob; // recebe qual o tipo do mob
	Arma arma;						// o mob possui uma arma só. Aqui temos de aplicar uma das armas do struct Armas
	int vida;
	int raioVisao; // o raio de visão pode variar entre 1 e 10 (provisório). o raio de visão mede-se em quantas 'casas' o mob consegue ver o jogador e começar a atacar
} Mob;

typedef struct statusMob
{
	Coordenadas posicao;
	Mob mob; // qual o mob e as suas características
} StatusMobs;

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

typedef enum elementosDoMapa
{
	Vazio,						/*   */
	Jogador,					/* @ */
	Mobs,							/* M - com foreground ou background vermelho */
	NPC,							/* & */
	Parede,						/* # */
	PortaNormal,			/* + - serve para fechar as salas, no futuro se for possível implementar o conceito de chaves escondidas */
	PortaProximoMapa, /* +++|+++|+++ - serve para mudar de mapa */
} ElementosDoMapa;

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

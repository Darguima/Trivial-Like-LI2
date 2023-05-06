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
	GameOver,
} Scene;

typedef enum colors
{
	WhiteBlack,
	YellowBlack,
	BlueBlack,
	GreenBlack,
	BlackYellow,
	BlackRed,
} Colors;

typedef struct coordenadas
{
	int x, y;
} Coordenadas;

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

typedef struct armaNoMapa
{
	Coordenadas posicao;
	int available; /* 1 if still available on a map; 0 if was already collected */
	Arma arma;
} ArmaNoMapa;

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

typedef struct mobNoMapa
{
	Coordenadas posicao;
	Mob mob;
} MobNoMapa;

typedef struct statusJogador
{
	Coordenadas posicao;
	char *username;
	int vida; // valor entre 0 e 100
	Arma armaPrincipal;
	Arma armaSecundaria;
	int dinheiro;
	int numMapaAtual; /* Quantas mapas já foram passados */
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
	MobNoMapa *mobs;
	ArmaNoMapa *armas;
	char *mensagem_descricao;						 /* Mensagem para mostrar um texto relevante. ex. algum informação do mapa, arma ou mob */
	char *mensagem_controlos; /* Mensagem para mostrar um como interagir com o mapa */
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
	Moeda,						/* c */
} ElementosDoMapa;

typedef struct terminal
{
	int height;
	int width;
} Terminal;

typedef struct mapa
{
	Terminal terminal;
	int height;
	int width;
	ElementosDoMapa **matrix;
} Mapa;

typedef struct state
{
	Scene sceneAtual;

	ControlosMenu controloMenu;

	JogoAtual jogoAtual;
	Mapa mapa;

} State;

State criarEstado(int colunas, int linhas);

extern Arma const punhos;
extern Arma const garras;
extern Arma const espadaOxidada;
extern Arma const espadaLonga;
extern Arma const arco;
extern Arma const acido;
extern Arma const cetro;

extern int const armasNoMapaLength;
extern int const catalogoArmasLength;
extern Arma const catalogoArmas[];

extern Mob const esqueleto1;
extern Mob const esqueleto2;
extern Mob const soldadoEsqueleto1;
extern Mob const vampiro1;
extern Mob const vampiro2;
extern Mob const mutante1;
extern Mob const mutante2;
extern Mob const aranha1;
extern Mob const aranha2;
extern Mob const zombie1;

extern int const mobsNoMapaLength;
extern int const catalogoMobsLength;
extern Mob const catalogoMobs[];

#endif

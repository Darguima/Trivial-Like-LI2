#include "state.h"

void start_state_colors()
{
  /* Starting colors & colors pairs */
  start_color();

  init_color(FG_MapaVisivel, 1000, 1000, 1000);
  init_color(FG_MapaMemoria, 250, 250, 250);
  init_color(FG_MapaDesconhecido, 100, 100, 100);

  init_color(BG_MapaVisivel, 128 * 4, 98 * 4, 69 * 4);
  init_color(BG_MapaMemoria, 76 * 4, 59 * 4, 43 * 4);
  init_color(BG_MapaDesconhecido, 125, 125, 125);

  init_color(FG_Portal, 54 * 4, 27 * 4, 111 * 4);
  init_color(FG_Player, 0, 0, 1000);
  init_color(FG_Moeda, 1000, 1000, 0);
  init_color(FG_Arma, 0, 1000, 0);
  init_color(FG_Objeto, 100 * 4, 150 * 4, 250 * 4);
  init_color(FG_Mob, 1000, 0, 0);
  
  init_color(BG_Parede, 144 * 4, 145 * 4, 131 * 4);
  init_color(BG_ParedeNaoVisivel, 68 * 4, 72 * 4, 71 * 4);

  init_pair(WhiteBlack, COLOR_WHITE, COLOR_BLACK);
  init_pair(YellowBlack, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BlueBlack, COLOR_BLUE, COLOR_BLACK);
  init_pair(GreenBlack, COLOR_GREEN, COLOR_BLACK);
  init_pair(BlackYellow, COLOR_BLACK, COLOR_YELLOW);
  init_pair(BlackRed, COLOR_BLACK, COLOR_RED);
  init_pair(RedBlack, COLOR_RED, COLOR_BLACK);

  init_pair(MapaPlayerColor, FG_Player, BG_MapaVisivel);
  init_pair(MapaPlayerSobAtaqueColor, FG_Player, FG_Mob);

  init_pair(MapaVisivelColor, FG_MapaVisivel, BG_MapaVisivel);
  init_pair(MapaMemoriaColor, FG_MapaMemoria, BG_MapaMemoria);
  init_pair(MapaDesconhecidoColor, FG_MapaDesconhecido, BG_MapaDesconhecido);

  init_pair(PortalColor, FG_Portal, FG_Portal);
  init_pair(MoedaColor, FG_Moeda, BG_MapaVisivel);
  init_pair(ArmaColor, FG_Arma, BG_MapaVisivel);
  init_pair(ObjetoColor, FG_Objeto, BG_MapaVisivel);
  init_pair(MobColor, FG_Mob, BG_MapaVisivel);
  
  init_pair(ParedeColor, BG_Parede, BG_Parede);
  init_pair(ParedeNaoVisivelColor, BG_ParedeNaoVisivel, BG_ParedeNaoVisivel);

  init_pair(ArmaBox, FG_Arma, COLOR_BLACK);
  init_pair(ObjetoBox, FG_Objeto, COLOR_BLACK);
  init_pair(MobBox, FG_Mob, COLOR_BLACK);
}
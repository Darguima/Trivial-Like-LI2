#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "../../state.h"
#include "../../MapaUtils/mapaUtils.h"
#include "../../SalvarJogo/salvarJogo.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaDefinicoes(WINDOW *window, State *state)
{
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
  getmaxyx(window, nrows, ncols);

  int y = (nrows / 2);
  int x = (ncols / 2);

  int iluminacao_ativa = state->jogoAtual.iluminacao_ativa;
  int mapa_desconhecido_ativo = state->jogoAtual.mapa_desconhecido_ativo;
  char *dificuldade;
  dificuldade = "Undefined";

  if (state->jogoAtual.dificuldade == FACIL)
    dificuldade = "Fácil";
  else if (state->jogoAtual.dificuldade == MEDIO)
    dificuldade = "Médio";
  else if (state->jogoAtual.dificuldade == DIFICIL)
    dificuldade = "Difícil";

  mvprintw(y - 11, x - 24, "     _____     _       _       _ _ _           ");
  mvprintw(y - 10, x - 24, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
  mvprintw(y - 9, x - 24, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
  mvprintw(y - 8, x - 24, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
  mvprintw(y - 7, x - 24, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___|   ");

  move(y - 4, 0);
  clrtoeol();
  mvprintw(
      y - 4, x - 22,
      "1.Alterar Tamanho do Mapa (Atual: %d x %d)",
      state->mapa.matrix_width, state->mapa.matrix_height);

  move(y - 1, 0);
  clrtoeol();
  mvprintw(
      y - 1, x - (31 + strlen(dificuldade)) / 2,
      "2.Alterar Dificuldade (Atual: %s)",
      dificuldade);

  move(y + 2, 0);
  clrtoeol();
  mvprintw(
      y + 2,
      mapa_desconhecido_ativo ? x - 15 : x - 13,
      mapa_desconhecido_ativo ? "3.Desativar Mapa Desconhecido" : "3.Ativar Mapa Desconhecido");

  move(y + 5, 0);
  clrtoeol();
  if (!mapa_desconhecido_ativo)
  {
    mvprintw(
        y + 5,
        iluminacao_ativa ? x - 12 : x - 11,
        iluminacao_ativa ? "4.Desativar Iluminação" : "4.Ativar Iluminação");
  }

  if (state->scenesVariables.definicoesSceneVars.ask_matrix_size == 1)
  {
    state->scenesVariables.definicoesSceneVars.ask_matrix_size = 0;
    int new_width, new_height;

    mvprintw(
        nrows - 14, 2, "Qual a largura (entre %d - 1500) do mapa? (escreve e enter para confirmar)",
        state->mapa.display_width);
    scanw("%d", &new_width);
    refresh();

    move(nrows - 14, 0);
    clrtoeol();

    mvprintw(
        nrows - 14, 2, "Qual a altura (entre %d - 1500) do mapa? (escreve e enter para confirmar)",
        state->mapa.display_height);
    scanw("%d", &new_height);
    refresh();

    if (state->mapa.display_height <= new_height && new_height <= 1500 && state->mapa.display_width <= new_width && new_width <= 1500)
    {
      libertar_matrix_mapa(state->mapa.matrix, state->mapa.matrix_width);

      state->mapa.matrix_height = new_height;
      state->mapa.matrix_width = new_width;

      state->mapa.matrix = alocar_matrix_mapa(state->mapa.matrix_width, state->mapa.matrix_height);

      save_settings_state(state);

      // Escrever o novo tamanho no ecrã
      desenhaDefinicoes(window, state);
    }

    move(nrows - 14, 0);
    clrtoeol();
  }

  mvprintw(nrows - 4, 2, "Selecione a opção com [1]-[%c]", mapa_desconhecido_ativo ? '3' : '4');
  mvwprintw(window, nrows - 2, 2, "Pressione [Q] para voltar atrás");

  refresh();
}
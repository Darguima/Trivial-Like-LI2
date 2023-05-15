#include <ncurses.h>

#include "../../state.h"

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

  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  box(window, 0, 0); // desenhar caixa

  mvwprintw(window, y, x, "Definicoes:");
  mvwprintw(window, y + 1, x, "Tamanho Mapa: %d x %d", state->mapa.matrix_height, state->mapa.matrix_width);
  
  mvwprintw(window, y + 2, x, "Dificuldade: %d", state->jogoAtual.dificuldade);
  
  mvwprintw(window, y + 3, x, "Iluminação: %d", state->jogoAtual.iluminacao_ativa);
  mvwprintw(window, y + 4, x, "Mapa Desconhecido: %d", state->jogoAtual.mapa_desconhecido_ativo);

  mvwprintw(window, nrows - 2, 2, "Pressione [Q] para voltar atrás");
}
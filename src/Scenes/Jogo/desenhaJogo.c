#include <ncurses.h>
#include "./visao.h"
#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaMapa(WINDOW *window, int largura_mapa, int altura_mapa, State *state)
{
	int bloco_visivel, bloco_descoberto;
	for (int x = 0; x < largura_mapa; x++)
	{
		for (int y = 0; y < altura_mapa; y++)
		{
			bloco_visivel = state->mapa.matrix[x][y].visivel;
			bloco_descoberto = state->mapa.matrix[x][y].descoberto;

			// Nunca foi visto
			if (bloco_descoberto == 0)
			{
				wattron(window, COLOR_PAIR(MapaDesconhecidoColor));
				mvwaddch(window, y, x, ' ');
				wattroff(window, COLOR_PAIR(MapaDesconhecidoColor));
				continue;
			}

			// Já foi, no passado, visto
			else if (bloco_visivel == 0)
			{
				wattron(window, COLOR_PAIR(MapaMemoriaColor));
			}

			else if (bloco_visivel == 1)
			{
				wattron(window, COLOR_PAIR(MapaVisivelColor));
			}

			switch (state->mapa.matrix[x][y].tipo)
			{
			case Parede:
				mvwaddch(window, y, x, '#');
				break;

			case Moeda:
				if (bloco_visivel)
					wattron(window, COLOR_PAIR(MoedaColor));

				mvwaddch(window, y, x, 'c');

				wattroff(window, COLOR_PAIR(MoedaColor));
				break;

			case Vazio:
				mvwaddch(window, y, x, ' ');
				break;

			default:
				mvwaddch(window, y, x, ' ');
				break;
			}

			wattroff(window, COLOR_PAIR(MapaVisivelColor));
			wattroff(window, COLOR_PAIR(MapaMemoriaColor));
			wattroff(window, COLOR_PAIR(MapaDesconhecidoColor));
		}
	}
}

void desenhaArmas(WINDOW *window, State *state)
{
	for (int arma = 0; arma < armasNoMapaLength; arma++)
	{
		ArmaNoMapa armaAtual = state->jogoAtual.armas[arma];

		if (!armaAtual.disponivel || state->mapa.matrix[armaAtual.posicao.x][armaAtual.posicao.y].descoberto == 0)
			continue;

		wattron(window, COLOR_PAIR(MapaMemoriaColor));
		if (state->mapa.matrix[armaAtual.posicao.x][armaAtual.posicao.y].visivel == 1)
		{
			wattroff(window, COLOR_PAIR(MapaMemoriaColor));
			wattron(window, COLOR_PAIR(ArmaColor));
		}

		mvwaddch(window, armaAtual.posicao.y, armaAtual.posicao.x, '%');

		wattroff(window, COLOR_PAIR(MapaMemoriaColor));
		wattroff(window, COLOR_PAIR(ArmaColor));
	}
}

void desenhaMobs(WINDOW *window, State *state)
{
	for (int mob_i = 0; mob_i < mobsNoMapaLength; mob_i++)
	{
		MobNoMapa mobAtual = state->jogoAtual.mobs[mob_i];

		if (!(mobAtual.mob.vida > 0) || state->mapa.matrix[mobAtual.posicao.x][mobAtual.posicao.y].descoberto == 0)
			continue;

		wattron(window, COLOR_PAIR(MapaMemoriaColor));
		if (state->mapa.matrix[mobAtual.posicao.x][mobAtual.posicao.y].visivel == 1)
		{
			wattroff(window, COLOR_PAIR(MapaMemoriaColor));
			wattron(window, COLOR_PAIR(MobColor));
		}

		mvwaddch(window, mobAtual.posicao.y, mobAtual.posicao.x, 'M');

		wattroff(window, COLOR_PAIR(MapaMemoriaColor));
		wattroff(window, COLOR_PAIR(MobColor));
	}
}

void desenhaJogo(WINDOW *window, State *state, int x, int y)
{
	ElementosDoMapa **mapa = state->mapa.matrix;

	visao(x, y, mapa, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);

	desenhaMapa(window, x, y, state);
	desenhaArmas(window, state);
	desenhaMobs(window, state);

	wattron(window, COLOR_PAIR(MapaPlayerColor));
	mvwaddch(window, state->jogoAtual.jogador.posicao.y, state->jogoAtual.jogador.posicao.x, '@');
	wattroff(window, COLOR_PAIR(MapaPlayerColor));

	wmove(window, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	wrefresh(window);

	return;
}

void desenhaMenusLaterais(WINDOW *window, State *state)
{
	UNUSED(window);

	// fronteira menu esquerdo
	WINDOW *l_win = newwin(state->mapa.height, 20, 5, 0);
	box(l_win, 0, 0);
	wrefresh(l_win);

	// fronteira menu direito
	WINDOW *r_win = newwin(state->mapa.height, 20, 5, state->mapa.terminal.width - 20);
	box(r_win, 0, 0);
	wrefresh(r_win);

	// vida
	mvprintw(7, 1, "%s", "VIDA:");
	mvprintw(7, 6, "%d", state->jogoAtual.jogador.vida);
	if (state->jogoAtual.jogador.vida > 96)
	{
		mvprintw(8, 1, "%s", "#################");
	}
	else if (state->jogoAtual.jogador.vida != 0)
	{
		for (int i = 0; i < (state->jogoAtual.jogador.vida / 6) + 1; i++)
		{
			mvprintw(8, 1 + i, "%s", "#");
		}
	}

	// arma principal
	attron(A_BOLD);
	mvprintw(11, 1, "%s", "PRINCIPAL ");
	attroff(A_BOLD);
	mvprintw(11, 12, "[Z]:");
	mvprintw(12, 1, "%s", state->jogoAtual.jogador.armaPrincipal.nome);
	mvprintw(13, 1, "%d pts de dano ", state->jogoAtual.jogador.armaPrincipal.dano);
	mvprintw(14, 1, "%d%% de acertar", state->jogoAtual.jogador.armaPrincipal.probabilidade);

	// arma secundaria
	attron(A_BOLD);
	mvprintw(16, 1, "%s", "SECUNDARIA ");
	attroff(A_BOLD);
	mvprintw(16, 12, "[X]:");
	mvprintw(17, 1, "%s", state->jogoAtual.jogador.armaSecundaria.nome);
	mvprintw(18, 1, "%d pts de dano", state->jogoAtual.jogador.armaSecundaria.dano);
	mvprintw(19, 1, "%d%% de acertar", state->jogoAtual.jogador.armaSecundaria.probabilidade);

	// dinheiro
	attron(A_BOLD);
	mvprintw(21, 1, "%s", "MOEDAS:");
	attroff(A_BOLD);
	mvprintw(21, 9, "%d", state->jogoAtual.jogador.dinheiro);

	// num mapa atual
	mvprintw(3, (state->mapa.terminal.width - 30) / 2, "M A P A  A T U A L : %d", state->jogoAtual.jogador.numMapaAtual);

	// mensagem
	mvprintw(state->mapa.terminal.height - 4, 20, "%s", state->jogoAtual.mensagem_descricao);
	mvprintw(state->mapa.terminal.height - 2, 20, "%s", state->jogoAtual.mensagem_controlos);
}
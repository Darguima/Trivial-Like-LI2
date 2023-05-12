#include <ncurses.h>
#include <string.h>
#include "./visao.h"
#include "../../state.h"
#include "../../MapaUtils/mapaUtils.h"

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

		mvwprintw(window, mobAtual.posicao.y, mobAtual.posicao.x, "%c", mobAtual.mob.charASCII);

		wattroff(window, COLOR_PAIR(MapaMemoriaColor));
		wattroff(window, COLOR_PAIR(MobColor));
	}
}

void desenhaJogo(WINDOW *window, State *state, int x, int y)
{
	ElementosDoMapa **mapa = state->mapa.matrix;

	visao(x, y, mapa, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);

	/*
	* A ordem pela qual aparecem as seguintes funções tem relevância no resultado final do mapa.
	* Quanto mais para o fim estiver a função, maior prioridade tem ao ser desenhada no mapa
	*/
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

	// num mapa atual
	mvwprintw(l_win, 1, 1, "MAPA ATUAL: %d", state->jogoAtual.jogador.numMapaAtual);

	// vida
	mvwprintw(l_win, 3, 1, "VIDA: %d", state->jogoAtual.jogador.vida);
	if (state->jogoAtual.jogador.vida > 96)
	{
		mvwprintw(l_win, 4, 1, "%s", "#################");
	}
	else if (state->jogoAtual.jogador.vida != 0)
	{
		for (int i = 0; i < (state->jogoAtual.jogador.vida / 6) + 1; i++)
		{
			mvwprintw(l_win, 4, 1 + i, "%s", "#");
		}
	}

	// arma principal
	attron(A_BOLD);
	mvwprintw(l_win, 7, 1, "%s", "PRINCIPAL ");
	attroff(A_BOLD);
	mvwprintw(l_win, 7, 12, "[Z]:");
	mvwprintw(l_win, 8, 1, "%s", state->jogoAtual.jogador.armaPrincipal.nome);
	mvwprintw(l_win, 9, 1, "%d pts de dano ", state->jogoAtual.jogador.armaPrincipal.dano);
	mvwprintw(l_win, 10, 1, "%d%% de acertar", state->jogoAtual.jogador.armaPrincipal.probabilidade);

	// arma secundaria
	attron(A_BOLD);
	mvwprintw(l_win, 12, 1, "%s", "SECUNDARIA ");
	attroff(A_BOLD);
	mvwprintw(l_win, 12, 12, "[X]:");
	mvwprintw(l_win, 13, 1, "%s", state->jogoAtual.jogador.armaSecundaria.nome);
	mvwprintw(l_win, 14, 1, "%d pts de dano", state->jogoAtual.jogador.armaSecundaria.dano);
	mvwprintw(l_win, 15, 1, "%d%% de acertar", state->jogoAtual.jogador.armaSecundaria.probabilidade);

	// dinheiro
	attron(A_BOLD);
	mvwprintw(l_win, 17, 1, "%s", "MOEDAS:");
	attroff(A_BOLD);
	mvwprintw(l_win, 17, 9, "%d", state->jogoAtual.jogador.dinheiro);
	wrefresh(l_win);

	// fronteira menu direito
	WINDOW *r_win = newwin(state->mapa.height, 20, 5, state->mapa.terminal.width - 20);
	box(r_win, 0, 0);
	wrefresh(r_win);

	// fronteira esquerda menu de baixo
	WINDOW *b_e_win = newwin(5, state->mapa.terminal.width / 2 - 16, state->mapa.height + 5, 0);
	box(b_e_win, 0, 0);
	// mensagem
	mvwprintw(b_e_win, 1, 1, "%s", state->jogoAtual.mensagem_descricao);
	mvwprintw(b_e_win, 3, 1, "%s", state->jogoAtual.mensagem_controlos);
	wrefresh(b_e_win);

	// fronteira direita menu de baixo
	WINDOW *b_d_win = newwin(5, state->mapa.terminal.width / 2 - 16, state->mapa.height + 5, state->mapa.terminal.width / 2 + 17);
	box(b_d_win, 0, 0);
	wrefresh(b_d_win);

	// fronteira centro menu de baixo
	WINDOW *b_c_win = newwin(5, 33, state->mapa.height + 5, state->mapa.terminal.width / 2 - 16);
	box(b_c_win, 0, 0);
	MobNoMapa *mobSobreposto;
	if (esta_sobre_mob(state, &mobSobreposto) && mobSobreposto->mob.vida > 0)
	{
		float vidaP = (float)mobSobreposto->mob.vida / mobSobreposto->mob.vidaMaxima;

		char moblen = (strlen(mobSobreposto->mob.nome)) / 2;

		// desenha a vida do mob
		mvwprintw(b_c_win, 1, 14 - moblen, "%s [%d]", mobSobreposto->mob.nome, mobSobreposto->mob.vida);

		for (int i = 0; i < 15; i++)
		{
			if ((float)i / 18 < vidaP)
			{
				mvwprintw(b_c_win, 3, 9 + i, "#");
			}
		}
	}
	ArmaNoMapa *armaSobreposta;
	if (esta_sobre_arma(state, &armaSobreposta) && armaSobreposta->disponivel)
	{
		char armaLen = (strlen(armaSobreposta->arma.nome)) / 2;

		//desenha nome da arma
		mvwprintw(b_c_win, 1, 16 - armaLen, "%s", armaSobreposta->arma.nome);
		mvwprintw(b_c_win, 2, 9, "%d pts de dano", armaSobreposta->arma.dano);
		mvwprintw(b_c_win, 3, 9, "%d%% de acertar", armaSobreposta->arma.probabilidade);




	}
	
	wrefresh(b_c_win);

	// desenha TriviaLike
	mvprintw(0, state->mapa.terminal.width / 2 - 20, "     _____     _       _       _ _ _            ");
	mvprintw(1, state->mapa.terminal.width / 2 - 20, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
	mvprintw(2, state->mapa.terminal.width / 2 - 20, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
	mvprintw(3, state->mapa.terminal.width / 2 - 20, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
	mvprintw(4, state->mapa.terminal.width / 2 - 20, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___| ");
}
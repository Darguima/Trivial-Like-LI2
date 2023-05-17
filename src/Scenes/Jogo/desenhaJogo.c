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

void desenhaMapa(WINDOW *window, State *state, int initial_x, int final_x, int initial_y, int final_y)
{
	int bloco_visivel, bloco_descoberto;

	for (int window_x = 0, map_x = initial_x; map_x < final_x; window_x++, map_x++)
	{
		for (int window_y = 0, map_y = initial_y; map_y < final_y; window_y++, map_y++)
		{
			bloco_visivel = state->mapa.matrix[map_x][map_y].visivel;
			bloco_descoberto = state->mapa.matrix[map_x][map_y].descoberto;

			// Nunca foi visto
			if (bloco_descoberto == 0)
			{
				wattron(window, COLOR_PAIR(MapaDesconhecidoColor));
				mvwaddch(window, window_y, window_x, ' ');
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

			switch (state->mapa.matrix[map_x][map_y].tipo)
			{
			case Parede:
				mvwaddch(window, window_y, window_x, '#');
				break;

			case Moeda:
				if (bloco_visivel)
					wattron(window, COLOR_PAIR(MoedaColor));

				mvwaddch(window, window_y, window_x, 'c');

				wattroff(window, COLOR_PAIR(MoedaColor));
				break;

			case Vazio:
				mvwaddch(window, window_y, window_x, ' ');
				break;

			default:
				mvwaddch(window, window_y, window_x, ' ');
				break;
			}

			wattroff(window, COLOR_PAIR(MapaVisivelColor));
			wattroff(window, COLOR_PAIR(MapaMemoriaColor));
			wattroff(window, COLOR_PAIR(MapaDesconhecidoColor));
		}
	}
}

void desenhaArmas(WINDOW *window, State *state, int initial_x, int initial_y)
{
	for (int arma = 0; arma < state->mapa.qntArmasNoMapaLength; arma++)
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

		mvwaddch(window, armaAtual.posicao.y - initial_y, armaAtual.posicao.x - initial_x, '%');

		wattroff(window, COLOR_PAIR(MapaMemoriaColor));
		wattroff(window, COLOR_PAIR(ArmaColor));
	}
}

void desenhaObjetos(WINDOW *window, State *state, int initial_x, int initial_y)
{
	for (int objeto = 0; objeto < state->mapa.qntObjetosNoMapaLength; objeto++)
	{
		ObjetoNoMapa objetoAtual = state->jogoAtual.objetos[objeto];

		if (!objetoAtual.disponivel || state->mapa.matrix[objetoAtual.posicao.x][objetoAtual.posicao.y].descoberto == 0)
			continue;

		wattron(window, COLOR_PAIR(MapaMemoriaColor));
		if (state->mapa.matrix[objetoAtual.posicao.x][objetoAtual.posicao.y].visivel == 1)
		{
			wattroff(window, COLOR_PAIR(MapaMemoriaColor));
			wattron(window, COLOR_PAIR(ObjetoColor));
		}

		mvwaddch(window, objetoAtual.posicao.y - initial_y, objetoAtual.posicao.x - initial_x, 'P');

		wattroff(window, COLOR_PAIR(MapaMemoriaColor));
		wattroff(window, COLOR_PAIR(ObjetoColor));
	}
}

void desenhaMobs(WINDOW *window, State *state, int initial_x, int initial_y)
{
	for (int mob_i = 0; mob_i < state->mapa.qntMobsNoMapaLength; mob_i++)
	{
		MobNoMapa mobAtual = state->jogoAtual.mobs[mob_i];

		if (state->mapa.matrix[mobAtual.posicao.x][mobAtual.posicao.y].visivel == 0 || !(mobAtual.mob.vida > 0))
			continue;

		wattron(window, COLOR_PAIR(MobColor));
		mvwprintw(window, mobAtual.posicao.y - initial_y, mobAtual.posicao.x - initial_x, "%c", mobAtual.mob.charASCII);
		wattroff(window, COLOR_PAIR(MobColor));
	}
}

void desenhaJogo(WINDOW *window, State *state)
{
	ElementosDoMapa **mapa = state->mapa.matrix;

	if (state->jogoAtual.iluminacao_ativa)
	{
		visao(state->mapa.matrix_width, state->mapa.matrix_height, mapa, state->jogoAtual.jogador.posicao.x, state->jogoAtual.jogador.posicao.y);
	}

	Coordenadas player_pos = state->jogoAtual.jogador.posicao;
	int display_width = state->mapa.display_width,
			display_height = state->mapa.display_height,
			matrix_width = state->mapa.matrix_width,
			matrix_height = state->mapa.matrix_height;

	int initial_x = player_pos.x - (display_width - 1) / 2,
			final_x = initial_x + display_width,
			initial_y = player_pos.y - (display_height - 1) / 2,
			final_y = initial_y + display_height;

	if (initial_x < 0)
	{
		initial_x = 0;
		final_x = display_width;
	}
	else if (final_x > matrix_width)
	{
		initial_x = matrix_width - display_width;
		final_x = matrix_width;
	}

	if (initial_y < 0)
	{
		initial_y = 0;
		final_y = display_height;
	}
	else if (final_y > matrix_height)
	{
		initial_y = matrix_height - display_height;
		final_y = matrix_height;
	}

	/*
	 * A ordem pela qual aparecem as seguintes funções tem relevância no resultado final do mapa.
	 * Quanto mais para o fim estiver a função, maior prioridade tem ao ser desenhada no mapa
	 */

	// as moedas são gravadas dentro do mapa, então a sua prioridade é igual a este
	desenhaMapa(window, state, initial_x, final_x, initial_y, final_y);
	desenhaArmas(window, state, initial_x, initial_y);
	desenhaObjetos(window, state, initial_x, initial_y);
	desenhaMobs(window, state, initial_x, initial_y);

	MobNoMapa *mob;
	wattron(window, COLOR_PAIR(!esta_sobre_mob(state, &mob) ? MapaPlayerColor : MapaPlayerSobAtaqueColor));
	mvwaddch(window, state->jogoAtual.jogador.posicao.y - initial_y, state->jogoAtual.jogador.posicao.x - initial_x, '@');
	wattroff(window, COLOR_PAIR(MapaPlayerColor));
	wattroff(window, COLOR_PAIR(MapaPlayerSobAtaqueColor));

	wrefresh(window);

	return;
}

void desenhaMenusLaterais(WINDOW *window, State *state)
{
	UNUSED(window);

	// fronteira menu esquerdo
	WINDOW *l_win = newwin(state->mapa.display_height, 20, 5, 0);
	box(l_win, 0, 0);

	// num mapa atual
	mvwprintw(l_win, 1, 1, "MAPA ATUAL: %d", state->jogoAtual.jogador.numMapaAtual);

	// vida
	mvwprintw(l_win, 3, 1, "VIDA: %d/%d", state->jogoAtual.jogador.vida ,state->jogoAtual.jogador.vidaMaxima);

	float vida100 = (float)state->jogoAtual.jogador.vida / 100;

	for (int i = 0; i < 15; i++)
		{
			if ((float)i / 18 < vida100)
			{
				mvwprintw(l_win, 4, 1 + i, "#");
			}
		}
	if (state->jogoAtual.jogador.vidaMaxima > 100)
	{
		float vida200 = ((float)state->jogoAtual.jogador.vida - 100) / 100;
		for (int i = 0; i < 15; i++)
		{
			if ((float)i / 18 < vida200)
			{
				wattron(l_win,COLOR_PAIR(YellowBlack));
				mvwprintw(l_win, 5, 1 + i, "#");
				wattroff(l_win,COLOR_PAIR(YellowBlack));
			}
		}
	}
	if (state->jogoAtual.jogador.vidaMaxima > 200)
	{
		float vida300 = ((float)state->jogoAtual.jogador.vida - 200) / 100;
		for (int i = 0; i < 15; i++)
		{
			if ((float)i / 18 < vida300)
			{
				wattron(l_win,COLOR_PAIR(YellowBlack));
				mvwprintw(l_win, 6, 1 + i, "#");
				wattroff(l_win,COLOR_PAIR(YellowBlack));
			}
		}
	}

	// Vida Máxima

	// arma principal
	attron(A_BOLD);
	mvwprintw(l_win, 8, 1, "%s", "PRINCIPAL ");
	attroff(A_BOLD);
	mvwprintw(l_win, 8, 12, "[Z]:");
	mvwprintw(l_win, 9, 1, "%s", state->jogoAtual.jogador.armaPrincipal.nome);
	mvwprintw(l_win, 10, 1, "%d pts de dano ", state->jogoAtual.jogador.armaPrincipal.dano);
	mvwprintw(l_win, 11, 1, "%d%% de acertar", state->jogoAtual.jogador.armaPrincipal.probabilidade);

	// arma secundaria
	attron(A_BOLD);
	mvwprintw(l_win, 13, 1, "%s", "SECUNDARIA ");
	attroff(A_BOLD);
	mvwprintw(l_win, 13, 12, "[X]:");
	mvwprintw(l_win, 14, 1, "%s", state->jogoAtual.jogador.armaSecundaria.nome);
	mvwprintw(l_win, 15, 1, "%d pts de dano", state->jogoAtual.jogador.armaSecundaria.dano);
	mvwprintw(l_win, 16, 1, "%d%% de acertar", state->jogoAtual.jogador.armaSecundaria.probabilidade);

	// dinheiro
	attron(A_BOLD);
	mvwprintw(l_win, 18, 1, "%s", "MOEDAS:");
	attroff(A_BOLD);
	mvwprintw(l_win, 18, 9, "%d", state->jogoAtual.jogador.dinheiro);
	wrefresh(l_win);

	// fronteira menu direito
	WINDOW *r_win = newwin(state->mapa.display_height, 20, 5, state->mapa.terminal.width - 20);
	box(r_win, 0, 0);
	
	int *quantidades = state->jogoAtual.inventarioQuantidades;

	mvwprintw(r_win, 1, 1, "[1]Pocao Vida P");
	mvwprintw(r_win, 2, 1, "................X%d", quantidades[0]);

	mvwprintw(r_win, 5, 1, "[2]Pocao Vida G");
	mvwprintw(r_win, 6, 1, "................X%d", quantidades[1]);

	mvwprintw(r_win, 9, 1, "[3]Pocao Vida D");
	mvwprintw(r_win, 10, 1, "................X%d", quantidades[2]);

	mvwprintw(r_win, 13, 1, "[4]Pocao Aumento");
	mvwprintw(r_win, 14, 1, "................X%d", quantidades[3]);

	mvwprintw(r_win, 17, 1, "[5]Pocao Magica");
	mvwprintw(r_win, 18, 1, "................X%d", quantidades[4]);

	mvwprintw(r_win, 21, 1, "[6]Portal de Bolso");
	mvwprintw(r_win, 22, 1, "................X%d", quantidades[5]);
	wrefresh(r_win);

	// fronteira esquerda menu de baixo
	WINDOW *b_e_win = newwin(5, state->mapa.terminal.width / 2 - 16, state->mapa.display_height + 5, 0);
	box(b_e_win, 0, 0);
	// mensagem
	mvwprintw(b_e_win, 1, 1, "%s", state->jogoAtual.mensagem_descricao);
	mvwprintw(b_e_win, 3, 1, "%s", state->jogoAtual.mensagem_controlos);
	wrefresh(b_e_win);

	// fronteira direita menu de baixo
	WINDOW *b_d_win = newwin(5, state->mapa.terminal.width / 2 - 16, state->mapa.display_height + 5, state->mapa.terminal.width / 2 + 17);
	box(b_d_win, 0, 0);

	mvwprintw(b_d_win, 1, 1, "%s", state->jogoAtual.mensagem_inventario);
	mvwprintw(b_d_win, 3, 1, "%s", state->jogoAtual.mensagem_inventario_controlos);

	wrefresh(b_d_win);

	// fronteira centro menu de baixo
	WINDOW *b_c_win = newwin(5, 33, state->mapa.display_height + 5, state->mapa.terminal.width / 2 - 16);
	box(b_c_win, 0, 0);

	ArmaNoMapa *armaSobreposta;
	if (esta_sobre_arma(state, &armaSobreposta))
	{
		char armaLen = (strlen(armaSobreposta->arma.nome)) / 2;

		wbkgd(b_c_win, COLOR_PAIR(ArmaBox));

		// desenha nome da arma
		mvwprintw(b_c_win, 1, 16 - armaLen, "%s", armaSobreposta->arma.nome);
		mvwprintw(b_c_win, 2, 9, "%d pts de dano", armaSobreposta->arma.dano);
		mvwprintw(b_c_win, 3, 9, "%d%% de acertar", armaSobreposta->arma.probabilidade);
	}

	ObjetoNoMapa *objetoSobreposto;
	if (esta_sobre_objeto(state, &objetoSobreposto))
	{
		char objetoLen = (strlen(objetoSobreposto->objeto.nome)) / 2;

		wbkgd(b_c_win, COLOR_PAIR(ObjetoBox));

		// desenha nome da arma
		mvwprintw(b_c_win, 1, 16 - objetoLen, "%s", objetoSobreposto->objeto.nome);
	}

	MobNoMapa *mobSobreposto;
	if (esta_sobre_mob(state, &mobSobreposto))
	{
		float vidaP = (float)mobSobreposto->mob.vida / mobSobreposto->mob.vidaMaxima;

		char moblen = (strlen(mobSobreposto->mob.nome)) / 2;

		wbkgd(b_c_win, COLOR_PAIR(RedBlack));

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

	wrefresh(b_c_win);

	// desenha TriviaLike
	mvprintw(0, state->mapa.terminal.width / 2 - 20, "     _____     _       _       _ _ _            ");
	mvprintw(1, state->mapa.terminal.width / 2 - 20, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
	mvprintw(2, state->mapa.terminal.width / 2 - 20, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
	mvprintw(3, state->mapa.terminal.width / 2 - 20, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
	mvprintw(4, state->mapa.terminal.width / 2 - 20, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___| ");
}




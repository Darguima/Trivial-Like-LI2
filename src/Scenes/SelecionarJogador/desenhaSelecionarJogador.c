#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void desenhaSelecionarJogador(WINDOW *window, State *state)
{
  UNUSED(window);
  UNUSED(state);

  int nrows, ncols;
  getmaxyx(stdscr, nrows, ncols);
  int y = (nrows / 2);
  int x = (ncols / 2);

  move(nrows - 14, 0);
  clrtoeol();

  move(nrows - 7, 0);
  clrtoeol();

  mvprintw(y - 11, x - 24, "     _____     _       _       _ _ _           ");
  mvprintw(y - 10, x - 24, "    |_   _| __(_)_   _(_) __ _| (_) | _____    ");
  mvprintw(y - 9, x - 24, "      | || '__| \\ \\ / / |/ _` | | | |/ / _ \\   ");
  mvprintw(y - 8, x - 24, "      | || |  | |\\ V /| | (_| | | |   <  __/   ");
  mvprintw(y - 7, x - 24, "      |_||_|  |_| \\_/ |_|\\__,_|_|_|_|\\_\\___|   ");

  mvaddstr(y - 3, x - 7, "Escolha o save");
  mvaddstr(y + 0, x - 7, "1.");
  mvaddstr(y + 2, x - 7, "2.");
  mvaddstr(y + 4, x - 7, "3.");
  mvaddstr(nrows - 7, 2, "Para apagar saves pressione [D]");
  mvaddstr(nrows - 5, 2, "Pressione [1]-[3] para escolher o save");
  mvaddstr(nrows - 4, 2, "Pressione [J] para um jogo rápido");
  mvaddstr(nrows - 2, 2, "Pressione [Q] para voltar");

  if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
  {
    mvaddstr(nrows - 7, 2, "Selecione o save a remover com [1]-[3] ( [A] - voltar )");
  }
  else if (state->scenesVariables.selecionarJogadorSceneVars.faildelete == 1)
  {
    mvaddstr(nrows - 7, 2, "Erro a apagar save ( [A] - voltar )");
  }

  if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 1)
  {
    char str[80];
    mvaddstr(nrows - 14, 2, "Qual o username? ( [ENTER] para confirmar)");
    refresh();

    getnstr(str, 30);
    strcpy(state->jogoAtual.jogador.username, str);

    move(nrows - 14, 0);
    clrtoeol();

    mvprintw(nrows - 14, 2, "Username: %s - [J]", state->jogoAtual.jogador.username);
    refresh();
    state->scenesVariables.selecionarJogadorSceneVars.askUser = 2;
  }

  // print usernames
  char *string;
  FILE *fp;
  char buffer[1024];
  struct json_object *parsed_json;
  struct json_object *username;
  char filename[10];

  for (int i = 1; i <= 3; i++)
  {
    sprintf(filename, "%d.json", i);
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      move(y - 2 + (i * 2), x - 4);
      clrtoeol();
      mvaddstr(y - 2 + (i * 2), x - 4, "Novo Jogo");
    }
    else
    {
      if (fread(buffer, 1024, 1, fp))
      {
      }
      fclose(fp);
      parsed_json = json_tokener_parse(buffer);
      json_object_object_get_ex(parsed_json, "username", &username);
      string = (char *)json_object_get_string(username);
      mvaddstr(y - 2 + (i * 2), x - 4, string);
    }
  }

  box(window, 0, 0); // desenhar caixa
}
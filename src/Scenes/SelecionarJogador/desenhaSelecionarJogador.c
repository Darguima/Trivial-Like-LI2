#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "../../state.h"
#include "../../GeraMapa/geraMapa.h"

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
  
  geraMapa(state);

  int nrows, ncols;
  getmaxyx(stdscr, nrows, ncols);
  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  move(nrows - 14, 0);
  clrtoeol();

  move(nrows - 8, 0);
  clrtoeol();
  box(window, 0, 0); // desenhar caixa

  refresh();
  mvaddstr(y - 10, x - 17, "Selecione Jogo");
  mvaddstr(y, x - 17, "1.");
  mvaddstr(y + 2, x - 17, "2.");
  mvaddstr(y + 4, x - 17, "3.");
  mvaddstr(nrows - 6, 2, "Para apagar jogador pressione d");
  mvaddstr(nrows - 4, 2, "Pressione num jogador para jogar");
  mvaddstr(nrows - 2, 2, "Pressione q para voltar");

  if (state->scenesVariables.selecionarJogadorSceneVars.delete == 1)
  {
    mvaddstr(nrows - 8, 2, "Delete Ligado, pressione numero para escolher qual progresso quer apagar ('a' : desligar)");
  }
  else if (state->scenesVariables.selecionarJogadorSceneVars.faildelete == 1)
  {
    mvaddstr(nrows - 8, 2, "Erro a apagar ficheiro ('a' : apagar mensagem)");
  }

  if (state->scenesVariables.selecionarJogadorSceneVars.askUser == 1)
  {
    char str[80];
    mvaddstr(nrows - 14, 2, "Qual o teu username? (escreve e enter para confirmar)");
    refresh();
    getnstr(str, 30);
    strcpy(state->jogoAtual.jogador.username, str);
    mvprintw(nrows - 14, 2, "username: %s , pressione j para continuar com novo jogador ou outro numero para continuar com outro jogador", state->jogoAtual.jogador.username);
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
      move(y + (i - 1) * 2, x - 15);
      clrtoeol();
      mvaddstr(y + (i - 1) * 2, x - 15, "Novo Jogo");
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
      mvaddstr(y + (i - 1) * 2, x - 15, string);
    }
  }
}
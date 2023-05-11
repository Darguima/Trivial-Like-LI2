#include <ncurses.h>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void desenhaSelecionarJogador(WINDOW *window, State *state)
{
  UNUSED(window);
  UNUSED(state);

  geraMapa(state->mapa.width, state->mapa.height, state->mapa.matrix);

  int nrows, ncols;
  getmaxyx(stdscr, nrows, ncols);
  int y = (nrows / 2) - 4;
  int x = (ncols / 2) - 2;

  box(window, 0, 0); // desenhar caixa

  refresh();
  mvaddstr(y - 10, x - 17, "Selecione Jogo"); //
  mvaddstr(y, x - 17, "1.");
  mvaddstr(y + 2, x - 17, "2.");
  mvaddstr(y + 4, x - 17, "3.");

  mvaddstr(nrows - 4, 2, "Pressione num jogador para jogar");
  mvaddstr(nrows - 2, 2, "Pressione q para voltar");

  // usernames em 1. 2. 3.
  char *string;
  FILE *fp;
  char buffer[1024];
  // por username 1
  struct json_object *parsed_json;
  struct json_object *username;
  fp = fopen("1.json", "r");
  if (fp == NULL)
  {
    // Senao existir "Novo Jogo"
    mvaddstr(y, x - 15, "Novo Jogo");
  }
  else
  {
    if (fread(buffer, 1024, 1, fp)){}
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "username", &username);
    string = (char *)json_object_get_string(username);
    mvaddstr(y, x - 15, string);
  }

  // por username 2

  fp = fopen("2.json", "r");
  if (fp == NULL)
  {
    // Senao existir "Novo Jogo"
    mvaddstr(y+2, x - 15, "Novo Jogo");
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
    mvaddstr(y+2, x - 15, string);
  }

  // por username 3

  fp = fopen("3.json", "r");
  if (fp == NULL)
  {
    // Senao existir "Novo Jogo"
    mvaddstr(y+4, x - 15, "Novo Jogo");
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
    mvaddstr(y+4, x - 15, string);
  }
}
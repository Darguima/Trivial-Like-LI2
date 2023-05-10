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
#include <json-c/json.h>

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

  mvaddstr(nrows - 4, 2, "Pressione j para jogar");
  mvaddstr(nrows - 2, 2, "Pressione q para voltar");

  
  char *string;
  // por username 1
  FILE *fp1;
  char buffer1[1024];
  struct json_object *parsed_json1;
  struct json_object *username1;
  fp1 = fopen("1.json", "r");
  if (fread(buffer1, 1024, 1, fp1))
  {
  }
  fclose(fp1);
  parsed_json1 = json_tokener_parse(buffer1);
  json_object_object_get_ex(parsed_json1, "username", &username1);
  string = (char *)json_object_get_string(username1);
  mvaddstr(y, x - 15, string);
  // por username 2
  FILE *fp2;
  char buffer2[1024];
  struct json_object *parsed_json2;
  struct json_object *username2;
  fp2 = fopen("2.json", "r");
  if (fread(buffer2, 1024, 1, fp2))
  {
  }
  fclose(fp2);
  parsed_json2 = json_tokener_parse(buffer2);
  json_object_object_get_ex(parsed_json2, "username", &username2);
  string = (char *)json_object_get_string(username2);
  mvaddstr(y + 2, x - 15, string);
  // por username 3
  FILE *fp3;
  char buffer3[1024];
  struct json_object *parsed_json3;
  struct json_object *username3;
  fp3 = fopen("3.json", "r");
  if (fread(buffer3, 1024, 1, fp3))
  {
  }
  fclose(fp3);
  parsed_json3 = json_tokener_parse(buffer3);
  json_object_object_get_ex(parsed_json3, "username", &username3);
  string = (char *)json_object_get_string(username3);
  mvaddstr(y + 4, x - 15, string);
}
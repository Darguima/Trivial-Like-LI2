#include <ncurses.h>
#include <json-c/json.h>
#include "../state.h"

// salvar jogo pra um JSON
void save_game_state(const char *filename, int vida, const char *username, int numMapaAtual, int dinheiro, int armaPrincipal, int armaSecundaria)
{
	// Criar objeto JSON para reter estado do Jogo
	json_object *game_state = json_object_new_object();

	// Pares estado do Jogo
	json_object_object_add(game_state, "vida", json_object_new_int(vida));
	json_object_object_add(game_state, "username", json_object_new_string(username));
	json_object_object_add(game_state, "numMapaAtual", json_object_new_int(numMapaAtual));
	json_object_object_add(game_state, "dinheiro", json_object_new_int(dinheiro));
	json_object_object_add(game_state, "armaPrincipal", json_object_new_int(armaPrincipal));
	json_object_object_add(game_state, "armaSecundaria", json_object_new_int(armaSecundaria));

	// Converter objeto JSON para string
	const char *json_str = json_object_to_json_string_ext(game_state, JSON_C_TO_STRING_PRETTY);

	// Abrir ficheiro save para escrever
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Error: unable to open save file for writing\n");
		exit(1);
	}

	// Escrever JSON string para o ficheiro save
	fprintf(fp, "%s", json_str);

	// Fechar ficheiro libertar memoria
	fclose(fp);
	json_object_put(game_state);
}

//carregar jogo
void load_game_state(const char *filename, State *state)
{
	int a1, a2;
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *vida;
	struct json_object *username;
	struct json_object *numMapaAtual;
	struct json_object *dinheiro;
	struct json_object *armaPrincipal;
	struct json_object *armaSecundaria;

	// load ficheiro
	fp = fopen(filename, "r");
	if (fp != NULL)
	{

		if (fread(buffer, 1024, 1, fp))
		{
		}
		fclose(fp);
		parsed_json = json_tokener_parse(buffer);
		json_object_object_get_ex(parsed_json, "vida", &vida);
		json_object_object_get_ex(parsed_json, "username", &username);
		json_object_object_get_ex(parsed_json, "numMapaAtual", &numMapaAtual);
		json_object_object_get_ex(parsed_json, "dinheiro", &dinheiro);
		json_object_object_get_ex(parsed_json, "armaPrincipal", &armaPrincipal);
		json_object_object_get_ex(parsed_json, "armaSecundaria", &armaSecundaria);

		state->jogoAtual.jogador.vida = json_object_get_int(vida);
		state->jogoAtual.jogador.username = (char *)json_object_get_string(username);
		state->jogoAtual.jogador.numMapaAtual = json_object_get_int(numMapaAtual);
		state->jogoAtual.jogador.dinheiro = json_object_get_int(dinheiro);
		a1 = json_object_get_int(armaPrincipal);
		a2 = json_object_get_int(armaSecundaria);

		state->jogoAtual.jogador.armaPrincipal = catalogoArmas[a1]; 
		state->jogoAtual.jogador.armaSecundaria = catalogoArmas[a2];
	}
}
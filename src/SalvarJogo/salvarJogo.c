#include <ncurses.h>
#include <json-c/json.h>
#include "../state.h"

// salvar jogo pra um JSON
void save_game_state(const char *filename, int vida, const char *username, int numMapaAtual, int dinheiro, int armaPrincipalIndex, int armaSecundariaIndex)
{
	// Criar objeto JSON para reter estado do Jogo
	json_object *game_state = json_object_new_object();

	// Pares estado do Jogo
	json_object_object_add(game_state, "vida", json_object_new_int(vida));
	json_object_object_add(game_state, "username", json_object_new_string(username));
	json_object_object_add(game_state, "numMapaAtual", json_object_new_int(numMapaAtual));
	json_object_object_add(game_state, "dinheiro", json_object_new_int(dinheiro));
	json_object_object_add(game_state, "armaPrincipalIndex", json_object_new_int(armaPrincipalIndex));
	json_object_object_add(game_state, "armaSecundariaIndex", json_object_new_int(armaSecundariaIndex));

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

// carregar jogo
void load_game_state(const char *filename, State *state)
{
	int arma1_index, arma2_index;
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json,
			*vida,
			*username,
			*numMapaAtual,
			*dinheiro,
			*armaPrincipalIndex,
			*armaSecundariaIndex;

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
		json_object_object_get_ex(parsed_json, "armaPrincipalIndex", &armaPrincipalIndex);
		json_object_object_get_ex(parsed_json, "armaSecundariaIndex", &armaSecundariaIndex);

		state->jogoAtual.jogador.vida = json_object_get_int(vida);
		state->jogoAtual.jogador.username = (char *)json_object_get_string(username);
		state->jogoAtual.jogador.numMapaAtual = json_object_get_int(numMapaAtual);
		state->jogoAtual.jogador.dinheiro = json_object_get_int(dinheiro);

		arma1_index = json_object_get_int(armaPrincipalIndex);
		arma2_index = json_object_get_int(armaSecundariaIndex);

		state->jogoAtual.jogador.armaPrincipal = catalogoArmas[arma1_index];
		state->jogoAtual.jogador.armaSecundaria = catalogoArmas[arma2_index];
	}
}
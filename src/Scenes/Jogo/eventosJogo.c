#include <ncurses.h>
#include <json-c/json.h>
#include "../../state.h"

void mover_jogador(State *state, int dx, int dy)
{
	state->jogoAtual.jogador.posicao.x += dx;
	state->jogoAtual.jogador.posicao.y += dy;
}
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

void eventosJogo(State *state)
{
	char file[10]; 
	int key = getch();

	switch (key)
	{
	case 's':
		
		sprintf(file, "%d.json", state->jogoAtual.jogador.numSave);
		save_game_state(file, state->jogoAtual.jogador.vida, state->jogoAtual.jogador.username, state->jogoAtual.jogador.numMapaAtual, state->jogoAtual.jogador.dinheiro, state->jogoAtual.jogador.armaPrincipal.index, state->jogoAtual.jogador.armaSecundaria.index);

		break;
	case KEY_A1:
	case '7':
		mover_jogador(state, -1, -1);
		break;

	case KEY_UP:
	case '8':
		mover_jogador(state, -1, +0);
		break;

	case KEY_A3:
	case '9':
		mover_jogador(state, -1, +1);
		break;

	case KEY_LEFT:
	case '4':
		mover_jogador(state, +0, -1);
		break;

	case KEY_RIGHT:
	case '6':
		mover_jogador(state, +0, +1);
		break;

	case KEY_C1:
	case '1':
		mover_jogador(state, +1, -1);
		break;

	case KEY_DOWN:
	case '2':
		mover_jogador(state, +1, +0);
		break;

	case KEY_C3:
	case '3':
		mover_jogador(state, +1, +1);
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}
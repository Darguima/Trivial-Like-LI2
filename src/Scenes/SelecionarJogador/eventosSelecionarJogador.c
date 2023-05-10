#include <ncurses.h>
#include <json-c/json.h>
#include "../../state.h"





void eventosSelecionarJogador(State *state)
{
	int a1,a2;
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *vida;
	struct json_object *username;
	struct json_object *numMapaAtual;
	struct json_object *dinheiro;
	struct json_object *armaPrincipal;
	struct json_object *armaSecundaria;

	int key = getch();

	switch (key)
	{
	case '1':
	    //jogador
		state->jogoAtual.jogador.n = 1;
        //load ficheiro 1
		fp = fopen("1.json", "r");
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

		if(a1==1){state->jogoAtual.jogador.armaPrincipal=punhos;}
		if(a1==2){state->jogoAtual.jogador.armaPrincipal=garras;}
		if(a1==3){state->jogoAtual.jogador.armaPrincipal=espadaOxidada;}
		if(a1==4){state->jogoAtual.jogador.armaPrincipal=espadaLonga;}
		if(a1==5){state->jogoAtual.jogador.armaPrincipal=arco;}
		if(a1==6){state->jogoAtual.jogador.armaPrincipal=acido;}
		if(a1==7){state->jogoAtual.jogador.armaPrincipal=cetro;}
		if(a2==1){state->jogoAtual.jogador.armaSecundaria=punhos;}
		if(a2==2){state->jogoAtual.jogador.armaSecundaria=garras;}
		if(a2==3){state->jogoAtual.jogador.armaSecundaria=espadaOxidada;}
		if(a2==4){state->jogoAtual.jogador.armaSecundaria=espadaLonga;}
		if(a2==5){state->jogoAtual.jogador.armaSecundaria=arco;}
		if(a2==6){state->jogoAtual.jogador.armaSecundaria=acido;}
		if(a2==7){state->jogoAtual.jogador.armaSecundaria=cetro;}
		
		break;
	case '2':
	    //jogador
		state->jogoAtual.jogador.n = 2;
        //load ficheiro 2
		fp = fopen("2.json", "r");
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
		
		if(a1==1){state->jogoAtual.jogador.armaPrincipal=punhos;}
		if(a1==2){state->jogoAtual.jogador.armaPrincipal=garras;}
		if(a1==3){state->jogoAtual.jogador.armaPrincipal=espadaOxidada;}
		if(a1==4){state->jogoAtual.jogador.armaPrincipal=espadaLonga;}
		if(a1==5){state->jogoAtual.jogador.armaPrincipal=arco;}
		if(a1==6){state->jogoAtual.jogador.armaPrincipal=acido;}
		if(a1==7){state->jogoAtual.jogador.armaPrincipal=cetro;}
		if(a2==1){state->jogoAtual.jogador.armaSecundaria=punhos;}
		if(a2==2){state->jogoAtual.jogador.armaSecundaria=garras;}
		if(a2==3){state->jogoAtual.jogador.armaSecundaria=espadaOxidada;}
		if(a2==4){state->jogoAtual.jogador.armaSecundaria=espadaLonga;}
		if(a2==5){state->jogoAtual.jogador.armaSecundaria=arco;}
		if(a2==6){state->jogoAtual.jogador.armaSecundaria=acido;}
		if(a2==7){state->jogoAtual.jogador.armaSecundaria=cetro;}

		break;
	case '3':
	    //jogador
		state->jogoAtual.jogador.n = 3;
        //load ficheiro 3
		fp = fopen("3.json", "r");
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
		
		if(a1==1){state->jogoAtual.jogador.armaPrincipal=punhos;}
		if(a1==2){state->jogoAtual.jogador.armaPrincipal=garras;}
		if(a1==3){state->jogoAtual.jogador.armaPrincipal=espadaOxidada;}
		if(a1==4){state->jogoAtual.jogador.armaPrincipal=espadaLonga;}
		if(a1==5){state->jogoAtual.jogador.armaPrincipal=arco;}
		if(a1==6){state->jogoAtual.jogador.armaPrincipal=acido;}
		if(a1==7){state->jogoAtual.jogador.armaPrincipal=cetro;}
		if(a2==1){state->jogoAtual.jogador.armaSecundaria=punhos;}
		if(a2==2){state->jogoAtual.jogador.armaSecundaria=garras;}
		if(a2==3){state->jogoAtual.jogador.armaSecundaria=espadaOxidada;}
		if(a2==4){state->jogoAtual.jogador.armaSecundaria=espadaLonga;}
		if(a2==5){state->jogoAtual.jogador.armaSecundaria=arco;}
		if(a2==6){state->jogoAtual.jogador.armaSecundaria=acido;}
		if(a2==7){state->jogoAtual.jogador.armaSecundaria=cetro;}
		break;

	case Jogo:
		break;
	case 'j':
		state->sceneAtual = Jogo;
		break;

	case 'q':
		state->sceneAtual = MenuInicial;
		break;
	}
}

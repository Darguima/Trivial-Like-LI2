#include <stdlib.h>
#include <ncurses.h>

#include "../../state.h"

/*
 * Enquanto os dois parametros da funcao não forem usados
 * esta macro é importante para prevenir o warning:
 * unused parameter window/state.
 * Quando forem as duas usadas pode ser removida
 */
#define UNUSED(x) (void)(x)

void eventosSair(State *state)
{
	UNUSED(state);

	int key = getch();

	switch (key)
	{
	case 'm':
		state->sceneAtual = MenuInicial;
		break;

	case 'q':
		endwin();
		exit(0);
		break;
	}
}
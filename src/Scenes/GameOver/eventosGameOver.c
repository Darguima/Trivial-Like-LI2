#include <stdlib.h>
#include <ncurses.h>

#include "../../state.h"

#define UNUSED(x) (void)(x)

void eventosGameOver(State *state)
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
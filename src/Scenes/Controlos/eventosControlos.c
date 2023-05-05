#include <ncurses.h>

#include "../../state.h"

#include "desenhaControlos.h"

void eventosControlos(State *state)
{
    int key = getch();

    switch (key)
    {
    case KEY_UP:
        (state->controloMenu.highlight)--;
        if ((state->controloMenu.highlight) == 0)
        {
            (state->controloMenu.highlight) = 1;
        }
        break;
    case KEY_DOWN:
        (state->controloMenu.highlight)++;
        if ((state->controloMenu.highlight) - 1 == NUM_OPTIONS)
        {
            (state->controloMenu.highlight) = NUM_OPTIONS;
        }
        break;
    case KEY_LEFT:
        (state->controloMenu.side) = 0;
        break;
    case KEY_RIGHT:
        (state->controloMenu.side) = 1;
        break;
    case 'q':
        state->sceneAtual = MenuInicial;
        break;
    default:
        break;
    }
    if ((state->controloMenu.side) == 1 && key == 10)
    {
        (state->controloMenu.help) = 1;
    }
    if ((state->controloMenu.side) == 0)
    {
        (state->controloMenu.help) = 0;
    }
}
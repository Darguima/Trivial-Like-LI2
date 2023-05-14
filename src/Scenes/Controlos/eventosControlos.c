#include <ncurses.h>

#include "../../state.h"

#include "desenhaControlos.h"

void eventosControlos(State *state)
{
    int key = getch();

    switch (key)
    {
    case KEY_UP:
        (state->scenesVariables.controlosSceneVars.highlight)--;
        if ((state->scenesVariables.controlosSceneVars.highlight) == 0)
        {
            (state->scenesVariables.controlosSceneVars.highlight) = 1;
        }
        break;
    case KEY_DOWN:
        (state->scenesVariables.controlosSceneVars.highlight)++;
        if ((state->scenesVariables.controlosSceneVars.highlight) - 1 == NUM_OPTIONS)
        {
            (state->scenesVariables.controlosSceneVars.highlight) = NUM_OPTIONS;
        }
        break;
    case KEY_LEFT:
        (state->scenesVariables.controlosSceneVars.side) = 0;
        break;
    case KEY_RIGHT:
        (state->scenesVariables.controlosSceneVars.side) = 1;
        break;
    case 'q':
        state->sceneAtual = MenuInicial;
        break;
    default:
        break;
    }
    if ((state->scenesVariables.controlosSceneVars.side) == 1 && key == 10)
    {
        (state->scenesVariables.controlosSceneVars.help) = 1;
    }
    if ((state->scenesVariables.controlosSceneVars.side) == 0)
    {
        (state->scenesVariables.controlosSceneVars.help) = 0;
    }
}
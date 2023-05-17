#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include "../../state.h"



int distancia ( Coordenadas player, Coordenadas mob ) {
int dif_x = pow(abs(player.x - mob.x),2);
int dif_y = pow(abs(player.y - mob.y),2);

return (sqrt(dif_x + dif_y)) ;



}
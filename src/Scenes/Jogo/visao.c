#include <math.h>
#include "../../state.h"
#include "../../MapaUtils/mapaUtils.h"

#define PI 3.14159265358979323846

void visao(int largura, int altura, ElementosDoMapa **mapa, int posX, int posY)
{
  for (int x = 0; x < largura; x++)
    for (int y = 0; y < altura; y++)
      mapa[x][y].visivel = 0;

  for (float anguloRad = 0; anguloRad <= 2 * PI; anguloRad += 0.017453)
  {
    for (int raio = 1; raio <= 20; raio++)
    {
      int blocoX, blocoY;

      blocoX = (posX + (raio * cos(anguloRad)));
      blocoY = (posY - (raio * sin(anguloRad)));

      if (!estaDentroDoMapa(blocoX, blocoY, largura, altura))
      {
        break;
      }

      mapa[blocoX][blocoY].visivel = 1;
      mapa[blocoX][blocoY].descoberto = 1;

      if (mapa[blocoX][blocoY].tipo == Parede)
        break;
    }
  }
  return;
}
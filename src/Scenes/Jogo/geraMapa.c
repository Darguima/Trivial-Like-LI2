#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "../../state.h"

int isok (int x , int y , int xmax, int ymax) {
	if (x>=0  && x<xmax && y >=0 && y<ymax) {return 1 ;}
	else {return 0;}
}




void povoarmapa57 (int linhas , int colunas ,int **arroz) {
	srand(time(NULL));
for (int i = 0 ; i<linhas; i++) {
	for (int n = 0 ; n< (colunas) ; n++) {
		if (i== 0 || i ==linhas-1  || n==0  || (i == linhas-1 && n == colunas-1) || n == colunas-1) {arroz[i][n]=1;}
		else {
			
			int temp = rand()%100;
			 if (temp <=42) {arroz[i][n]= 1;} 
			 else {arroz[i][n]=0;}
		}
		}
}
return ;
}

void copyall (int  x , int y , int aqui[x][y], int **ali) {
	for (int i = 0 ; i<x ; i++) {
		for(int j = 0 ; j<y ; j++) {
			aqui[i][j] = ali[i][j];
		}
	}
	return ;
}


void applycelular ( int x , int y , int **mapa) {
	for (int k = 0 ; k <3; k++) {
		int auxmap[x][y];
		copyall (x, y , auxmap, mapa);
		for (int s = 1 ; s<x ; s++ ) {
			for (int j = 1 ; j< y ; j++) {
				int windoh_count = 0 ;
				int windoh = 0 ;
				for (int a = s-1 ; a<= s+1 ; a++) {
					for (int b = j-1 ; b<= j+1 ; b++) {
						if (isok(a , b , x , y)) {
                           
                             if (auxmap[a][b] == 1 ) {windoh_count ++ ;}
						   
						}
						else {
							windoh_count ++;
						}
					}
				}
				for (int a = s-4 ; a<= s+4 ; a++) {
					for (int b = j-4 ; b<= j+4 ; b++) {
						if (isok(a , b , x , y)) {
                           
                             if (auxmap[a][b] == 1 ) {windoh++;}
						   
						}
						else {
							windoh ++;
						}
					}
				}
				


                if (windoh_count>=5 ||windoh<=2) {mapa[s][j] = 1;}
				else{mapa[s][j]= 0;}
			}
			

		} 




	}
for (int k = 0 ; k <2; k++) {
		int auxmap[x][y];
		copyall (x, y , auxmap, mapa);
		for (int s = 1 ; s<x ; s++ ) {
			for (int j = 1 ; j< y ; j++) {
				int windoh_count = 0 ;
				for (int a = s-1 ; a<= s+1 ; a++) {
					for (int b = j-1 ; b<= j+1 ; b++) {
						if (isok(a , b , x , y)) {
                           
                             if (auxmap[a][b] == 1 ) {windoh_count ++ ;}
						   
						}
						else {
							windoh_count ++;
						}
					}
				}
				


                if (windoh_count>=5 ) {mapa[s][j] = 1;}
				else{mapa[s][j]= 0;}
			}
			

		} 




	}

	return;
}




void geraMapa(int ncols , int nrows , int **mapa){

  povoarmapa57 (ncols-40 ,nrows-10 ,mapa );
  applycelular(ncols-40,nrows-10, mapa);


    return ;
}
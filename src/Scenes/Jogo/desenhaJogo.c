#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "../../state.h"



int isokk (int x , int y , int xmax, int ymax) {
	if (x>=0  && x<xmax && y >=0 && y<ymax) {return 1 ;}
	else {return 0;}
}
// void verificablocosaolado( int posX, int posY, int maxX, int maxY, int **mapa) {
// 	// if(blocoY <posY) {
// 	// 		if (blocoX <posX) {
// 	// 			int y_blocoAbaixo = blocoY+1;
// 	// 			int x_blocoAolado = blocoX+1;
// 	// 			if(isokk(blocoX,y_blocoAbaixo,maxX,maxY) && isokk(x_blocoAolado,blocoY,maxX,maxY)) {
//     //               if((mapa[blocoX][y_blocoAbaixo] >= 1 || mapa[x_blocoAolado][blocoY]>=1 ) || (mapa[x_blocoAolado][blocoY] == 11 )) {mapa[blocoX][blocoY] = 12;}
// 	// 			}
// 	// 			else {return;}
// 	// 		}
// 	// 	} 
// 	// 	return ;
// }

void visao(int x, int y, int **mapa,int posX,int posY) {
	for (int i = 0 ; i<x ; i++) {
		for (int n = 0 ; n< y ; n++) {
			if (mapa[i][n] == 1) { mapa[i][n]= 11;}
			else if (mapa[i][n] == 0 ) {mapa[i][n]= 10;}
			
		}

	}
	// se for visivel a parede passa para 1 e o chao para zero ;D
	
for (int i = 0 ; i<=360 ; i+=1 ) {
	float anguloRad;
	anguloRad = i * 0.017453 ;
	for (int j = 1 ; j<=20; j++ ) {
	int blocoX,blocoY;
    //    if (i<=90 ) {
	
		
    // //    if (i == 90) {
	// // 	blocoX = posX ;
	// // 	blocoY=posY -j;
		
    // //    if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	// //    else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// //    }
	// //    if (i == 0 ) {
	
	// // 	blocoX = posX +j ;
	// // 	blocoY=posY ;
    // //    if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	// //    else if (mapa[blocoX][blocoY]==11 ||  mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// //    }
	   
	// 	blocoX = (posX + (j*cos(anguloRad)))  ;
	// 	blocoY = (posY - (j*sin(anguloRad)) ) ;
	// 	if(!isokk(blocoX,blocoY,x,y)) {break;}
	// 	 if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	//    else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	   
	//    }
	//    else if (i>90 && i<=180){
	// 	// if(!isok(blocoX,blocoY,x,y)) {break;}
	// 	// if (i == 180) {
	// 	// 	blocoX = posX-j;
	// 	// 	blocoY=posY ;
	// 	// 	if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	//     //  else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// 	// }
	// 	// else {
	// 	blocoX = (posX + (j*cos(anguloRad)))  ;
	// 	blocoY = (posY - (j*sin(anguloRad)) ) ;
	// 		if(!isokk(blocoX,blocoY,x,y)) {break;}
	// 	 if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	//    else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// 	}
         
	   
	//    else if(i>180 && i<=270) {
	// // 	if(!isok(blocoX,blocoY,x,y)) {break;}
	// // 	if(i == 270) {
	// // 		blocoX = posX;
	// // 		blocoY=posY +j;
	// // 		if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	// //      else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// // 	}
	// // 	else {
	// // 		blocoX = (posX + (j*cos(anguloRad)))  ;
	// // 	blocoY = (posY - (j*sin(anguloRad)) ) ;
		
	// // 	 if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	// //    else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	// // 	}
    // //     // x por excesso , y por defeito
	// //    }
	// //    else {
    //  // x defeito , y defeito
	//      blocoX = (posX + (j*cos(anguloRad)))  ;
	// 	 blocoY = (posY - (j*sin(anguloRad)) ) ;
	// 		if(!isokk(blocoX,blocoY,x,y)) {break;}
		
	// 	 if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	//    else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY]==1) {mapa[blocoX][blocoY]= 1 ; break;}
	   

	// }
	// else {
		 blocoX = (posX + (j*cos(anguloRad)))  ;
		 blocoY = (posY - (j*sin(anguloRad)) ) ;
			if(!isokk(blocoX,blocoY,x,y)) {break;}


		// if(blocoY <posY) {
		// 	if (blocoX <posX) {
		// 		int y_blocoAbaixo = blocoY+1;
		// 		if(isokk(blocoX,y_blocoAbaixo,x,y)) {
        //           if( mapa[blocoX][y_blocoAbaixo] == 1 ||mapa[blocoX][y_blocoAbaixo]==11 ) {mapa[blocoX][blocoY] == 11;}
		// 		}
		// 		else {break;}
		// 	}
		// } 
		
		 else if (mapa[blocoX][blocoY]  == 10) {mapa[blocoX][blocoY] = 0;}
	   else if (mapa[blocoX][blocoY]==11 || mapa[blocoX][blocoY] == 1 ) {mapa[blocoX][blocoY]= 1 ;  break;}
	   // ! no segundo else if colocar || mapa[blocoX][blocoY] == 1 se nao funcionar  
	
}	



}
// verificablocosaolado(posX, posY, x , y , mapa);
return ;
}



// int isok (int x , int y , int xmax, int ymax) {
// 	if (x>=0  && x<xmax && y >=0 && y<ymax) {return 1 ;}
// 	else {return 0;}
// }




// void povoarmapa57 (int linhas , int colunas ,int **arroz) {
// 	srand(time(NULL));
// for (int i = 0 ; i<linhas; i++) {
// 	for (int n = 0 ; n< (colunas) ; n++) {
// 		if (i== 0 || i ==linhas-1  || n==0  || (i == linhas-1 && n == colunas-1) || n == colunas-1) {arroz[i][n]=1;}
// 		else {
			
// 			int temp = rand()%100;
// 			 if (temp <=42) {arroz[i][n]= 1;} 
// 			 else {arroz[i][n]=0;}
// 		}
// 		}
// }
// return ;
// }

// void copyall (int  x , int y , int aqui[x][y], int **ali) {
// 	for (int i = 0 ; i<x ; i++) {
// 		for(int j = 0 ; j<y ; j++) {
// 			aqui[i][j] = ali[i][j];
// 		}
// 	}
// 	return ;
// }


// void applycelular ( int x , int y , int **mapa) {
// 	for (int k = 0 ; k <3; k++) {
// 		int auxmap[x][y];
// 		copyall (x, y , auxmap, mapa);
// 		for (int s = 1 ; s<x ; s++ ) {
// 			for (int j = 1 ; j< y ; j++) {
// 				int windoh_count = 0 ;
// 				int windoh = 0 ;
// 				for (int a = s-1 ; a<= s+1 ; a++) {
// 					for (int b = j-1 ; b<= j+1 ; b++) {
// 						if (isok(a , b , x , y)) {
                           
//                              if (auxmap[a][b] == 1 ) {windoh_count ++ ;}
						   
// 						}
// 						else {
// 							windoh_count ++;
// 						}
// 					}
// 				}
// 				for (int a = s-4 ; a<= s+4 ; a++) {
// 					for (int b = j-4 ; b<= j+4 ; b++) {
// 						if (isok(a , b , x , y)) {
                           
//                              if (auxmap[a][b] == 1 ) {windoh++;}
						   
// 						}
// 						else {
// 							windoh ++;
// 						}
// 					}
// 				}
				


//                 if (windoh_count>=5 ||windoh<=2) {mapa[s][j] = 1;}
// 				else{mapa[s][j]= 0;}
// 			}
			

// 		} 




// 	}
// for (int k = 0 ; k <2; k++) {
// 		int auxmap[x][y];
// 		copyall (x, y , auxmap, mapa);
// 		for (int s = 1 ; s<x ; s++ ) {
// 			for (int j = 1 ; j< y ; j++) {
// 				int windoh_count = 0 ;
// 				for (int a = s-1 ; a<= s+1 ; a++) {
// 					for (int b = j-1 ; b<= j+1 ; b++) {
// 						if (isok(a , b , x , y)) {
                           
//                              if (auxmap[a][b] == 1 ) {windoh_count ++ ;}
						   
// 						}
// 						else {
// 							windoh_count ++;
// 						}
// 					}
// 				}
				


//                 if (windoh_count>=5 ) {mapa[s][j] = 1;}
// 				else{mapa[s][j]= 0;}
// 			}
			

// 		} 




// 	}

// 	return;
// }

// void gerarMapa (int ncols , int nrows , int **mapa) {
//   povoarmapa57 (ncols-40 ,nrows-10 ,mapa );
//   applycelular(ncols-40,nrows-10, mapa);
//   return;
// }
void desenhaJogo(WINDOW* window, State* state, int x, int y, int **mapa) {
	visao(x,y,mapa,state->jogoAtual.jogador.posicao.x,state->jogoAtual.jogador.posicao.y);
	wrefresh(window);
for (int i = 0 ; i<x ; i++) {
		for (int n = 0 ; n< y ; n++) {
			if(mapa[i][n] == 1  ) {mvwaddch(window,n, i, '#');}
			else {
				if (mapa[i][n] == 0) {mvwaddch(window,n, i, '.');}
				else {mvwaddch(window,n, i, ' ');}
              
			}
		}

	}
  mvwaddch(window,state->jogoAtual.jogador.posicao.y,state->jogoAtual.jogador.posicao.x , '@');
  wmove(window,state->jogoAtual.jogador.posicao.y,state->jogoAtual.jogador.posicao.x);
  wrefresh(window);
  
 
	return ;
}

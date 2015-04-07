#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

/*
  Associe un score (int) a une grille suivant ses chances de réussite
  en parcourant la grille et en vérifiant que depuis le coin haut gauche 
  la grille est trié dans l'orde croissant sur chaque ligne de gauche a droite
*/
int scoreGrid(grid g){
  int c=0;
  for(int i=1;i<GRID_SIDE;i++){
    for(int j=1;j<GRID_SIDE;j++){
      if((get_tile(g,i,j))!=0){
	 if(get_tile(g,i,j)<=get_tile(g,i-1,j))
	   c++;
	 else
	   c--;
	}
      }
    }
  }
  return c;
}
    /*
  On met dans un tableau les 4 grilles possible aprés chaque mouvements 
  l'indice étant associé au mouvement, puis on calcule grace a scoreGrid 
  la meilleure des grilles suivant l'apparition d'un deux ou d'un 4 dans 
  une case vide
  Note:UP=0,LEFT=1,DOWN=2,RIGHT=3
*/

dir ramification(grid g){
  int bestGrid;
  int maxMoyenneTest=0;
  int moyenneTest=0;
  int c;
  grid* t=malloc(sizeof(grid)*4);
  for(int i=0;i<3;i++){
    t[i]=new_grid();
    copy_grid(g,t[i]);
    do_move(t[i],i);
    for(int u=0;u<GRID_SIDE;u++){
      for(int v=0;v<GRID_SIDE;v++){
	if(get_tile(t[i],u,v)==0){
	  set_tile(t[i],u,v,2);
	  if(scoreGrid(t[i])>maxMoyenneTest){
	    moyenneTest+=scoreGrid(t[i]);
	  }
	  set_tile(t[i],u,v,4);
	  if(scoreGrid(t[i])>maxMoyenneTest){
	    moyenneTest+=scoreGrid(t[i]);
	  }
	  c+=2;
	}
      }
    }
    moyenneTest/=c;
    c=0;
    if(maxMoyenneTest<moyenneTest){
      bestGrid=i;
      maxMoyenneTest=moyenneTest;
    }
  }
  return bestGrid;
}


void main(void){
  grid test=new_grid();
  printf("Resultat:%d\n",scoreGrid(test));
  set_tile (test,0,0,4);
  set_tile (test,0,1,4);
  set_tile (test,0,2,2);
  set_tile (test,0,3,2);
  printf("Resultat:%d\n",ramification(test));
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "grid.h"

struct grid_s {
  unsigned long int score;
  unsigned int **tuiles;
};

grid new_grid(){
  grid the_grid = malloc(sizeof(struct grid_s));
  the_grid->score = 0;
  the_grid->tuiles = malloc(GRID_SIDE*sizeof(int*));
  for(int y=0;y<GRID_SIDE;y++) {
    the_grid->tuiles[y]=malloc(GRID_SIDE*sizeof(tile));
    for(int x=0;x<GRID_SIDE;x++){
      the_grid->tuiles[y][x]=0;
    }
  }
  return the_grid;
}

void delete_grid(grid g){
  for(int y=0;y<GRID_SIDE;y++) {
    free(g->tuiles[y]);
  }
  free(g->tuiles); 
  free(g);
}

void draw_grid(grid g){
  printf("-------------\n");
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      printf("%i",g->tuiles[y][x]);
    }
    printf("\n");
  }
  printf("-------------\n");
}

void copy_grid(grid src, grid dst){
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      dst->tuiles[y][x]=src->tuiles[y][x];
    }
  }
}

unsigned long int grid_score(grid g){
  return g->score;
}

tile get_tile(grid g,int x,int y){
  return g->tuiles[y][x];
}

void set_tile (grid g, int x, int y, tile t){
  g->tuiles[y][x]=t;
}

bool can_move(grid g,dir d){
  bool cm = false;
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=1;x<GRID_SIDE;x++){
      switch(d)
	{
	case UP:
	  if((g->tuiles[x-1][y]==0) ^ (g->tuiles[x][y]==g->tuiles[x-1][y]))
	    cm=true;
	  break;
	case LEFT:
	  if((g->tuiles[y][x-1]==0) ^ (g->tuiles[y][x]==g->tuiles[y][x-1]))
	    cm=true;
	  break;
	case DOWN:
	  if((g->tuiles[x][y]==0) ^ (g->tuiles[x-1][y]==g->tuiles[x][y]))
	    cm=true;
	  break;
	case RIGHT:
	  if((g->tuiles[y][x]==0) ^ (g->tuiles[y][x-1]==g->tuiles[y][x]))
	    cm=true;
	  break;
	}
    }
  }
  return cm;
}

bool game_over(grid g){
  return (!can_move(g,UP) && !can_move(g,DOWN) && !can_move(g,LEFT) && !can_move(g,RIGHT));
}

int tr_tab(int tab[], int *size){ //CHANGER NOM FCTION
  //printf("test:%i\n",tab[0]);
  int score=0;
  for(int i=1;i<*size;i++){
    if(tab[i-1]==tab[i]) {
      tab[i-1]+=1;
      score+=pow(2,tab[i-1]);
      for(int j=i+1;j<*size;j++){
	tab[j-1]=tab[j];
      }
      *size-=1;
    }
  }
  return score;
}

void do_move(grid g, dir d){ //GERER DUPLICATION DE CODE !! <3
  int size = 0;
  int tab[GRID_SIDE];
  if(can_move(g,d)) {
    switch(d)
      {
      case UP:
        for(int x=0;x<GRID_SIDE;x++){
	  size=0;
	  for(int y=0;y<GRID_SIDE;y++){
	    if(get_tile(g,x,y)!=0){
	      tab[size]=get_tile(g,x,y);
	      size+=1;
	    }
	  }
	  g->score+=tr_tab(tab,&size);
	  for(int y=0;y<GRID_SIDE;y++){
	    //printf("CTRL:x=%i|y=%i|size=%i|tab=%i\n",x,y,size,tab[y]);
	    if(y<size)
	      set_tile(g,x,y,tab[y]);
	    else
	      set_tile(g,x,y,0);
	  }
	}
	break;
      case LEFT:
        for(int y=0;y<GRID_SIDE;y++){
	  size=0;
	  for(int x=0;x<GRID_SIDE;x++){
	    if(get_tile(g,x,y)!=0){
	      tab[size]=get_tile(g,x,y);
	      size+=1;
	    }
	  }
	  g->score+=tr_tab(tab,&size);
	  for(int x=0;x<GRID_SIDE;x++){
	    if(x<size) //A MODIFIER
	      set_tile(g,x,y,tab[x]); //ICI AUSSI
	    else
	      set_tile(g,x,y,0);
	  }
	}
	break;
      case DOWN:
        for(int x=0;x<GRID_SIDE;x++){
	  size=0;
	  for(int y=GRID_SIDE-1;y>=0;y--){
	    if(get_tile(g,x,y)!=0){
	      tab[size]=get_tile(g,x,y);
	      size+=1;
	    }
	  }
	  g->score+=tr_tab(tab,&size);
	  for(int y=GRID_SIDE-1;y>=0;y--){
	    if(GRID_SIDE-y-1<size) //A MODIFIER
	      set_tile(g,x,y,tab[GRID_SIDE-y-1]); //ICI AUSSI
	    else
	      set_tile(g,x,y,0);
	  }
	}
	break;
      case RIGHT:
        for(int y=0;y<GRID_SIDE;y++){//x->y || y->x
	  size=0;
	  for(int x=GRID_SIDE-1;x>=0;x--){//x->y || y->x
	    if(get_tile(g,x,y)!=0){
	      tab[size]=get_tile(g,x,y);
	      size+=1;
	    }
	  }
	  g->score+=tr_tab(tab,&size);
	  for(int x=GRID_SIDE-1;x>=0;x--){//x->y || y->x
	    if(GRID_SIDE-x-1<size) //x->y || y->x
	      set_tile(g,x,y,tab[GRID_SIDE-x-1]); //x->y || y->x
	    else
	      set_tile(g,x,y,0);
	  }
	}
	break;
      }
  }
}

void add_tile(grid g){
  //DEBUT TABLEAU DES VIDES
  int **tab = malloc(GRID_SIDE*GRID_SIDE*sizeof(int*));
  int taille=0;
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      if(get_tile(g,x,y)==0){
        tab[taille] = malloc(2*sizeof(int));
	tab[taille][0]=x;
	tab[taille][1]=y;
	taille++;
      }
    }
  }
  //FIN TABLEAU DES VIDES
  if(taille>=1){
    //DEBUT RANDOM rand()%taille
    int alea = rand()%1000;
    int pos_alea = rand()%taille;
    if (alea<900)
      set_tile(g,tab[pos_alea][0],tab[pos_alea][1],1);
    else
      set_tile(g,tab[pos_alea][0],tab[pos_alea][1],2);
    //FIN RANDOM
  }

  //DEBUT FREE
  for(int i=0;i<taille;i++)
    free(tab[i]);
  free(tab);
  //FIN FREE
}

void play(grid g, dir d){
  if(can_move(g,d)) {
    do_move(g,d);
    add_tile(g);
  }
}

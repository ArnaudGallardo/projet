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
  dst->score=src->score;
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

void grid_to_tab(grid g, int tab[], int *size, int x, bool inverser, bool horizontal)
{
  *size=0;
  int tmp = x;
  for(int y=0;y<GRID_SIDE;y++){
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(get_tile(g,x,y)!=0){
      tab[*size]=get_tile(g,x,y);
      *size+=1;
    }
    if(horizontal)
      y=x;
  }
  if(inverser)
    inverser_tab(tab, size);
}

void inverser_tab(int tab[], int *size)
{
  int tmp;
  for(int i=0;i<*size/2;i++)
    {
      tmp = tab[i];
      tab[i]=tab[*size-i-1];
      tab[*size-i-1]=tmp;
    }
}

/**
 * \brief Copy an line array into a grid line
 * \param g the grid
 * \param tab the line array
 * \param size the size of the line array
 * \param x the position of the line in the grid
 */
void tab_to_grid(grid g, int tab[], int *size, int x, bool inverser, bool horizontal)
{
  int tmp = x;
  int tp;
  for(int y=0;y<GRID_SIDE;y++){
    tp = y;
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(inverser)
      {
	if(tp<GRID_SIDE-(*size))
	  set_tile(g,x,y,0);
	else
	  set_tile(g,x,y,tab[GRID_SIDE-tp-1]);
      }
    else
      {
	if(tp<*size)
	  set_tile(g,x,y,tab[tp]);
	else
	  set_tile(g,x,y,0);
      }
    if(horizontal)
      y=x;
  }
}

void do_move(grid g, dir d){ 
  int size = 0;
  int tab[GRID_SIDE];
  if(can_move(g,d)) {
    for(int x=0;x<GRID_SIDE;x++)
      {
	//Voir doc fonctions
	//d>=2 <=> d==DOWN || d==RIGHT
	//d%2 <=> d==LEFT || d==RIGHT
	grid_to_tab(g,tab,&size,x,(d>=2),(d%2));
	g->score+=tr_tab(tab,&size);
	tab_to_grid(g,tab,&size,x,(d>=2),(d%2));
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

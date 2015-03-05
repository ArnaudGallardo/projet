#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "grid.h"
#include "grid_utilities.h"

struct grid_s {
  unsigned long int score;
  unsigned int **tiles;
};

grid new_grid(){
  grid the_grid = malloc(sizeof(struct grid_s));
  the_grid->score = 0;
  the_grid->tiles = malloc(GRID_SIDE*sizeof(int*));
  for(int y=0;y<GRID_SIDE;y++) {
    the_grid->tiles[y]=malloc(GRID_SIDE*sizeof(tile));
    for(int x=0;x<GRID_SIDE;x++){
      the_grid->tiles[y][x]=0;
    }
  }
  return the_grid;
}

void delete_grid(grid g){
  for(int y=0;y<GRID_SIDE;y++) {
    free(g->tiles[y]);
  }
  free(g->tiles); 
  free(g);
}

void copy_grid(grid src, grid dst){
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      dst->tiles[y][x]=src->tiles[y][x];
    }
  }
  dst->score=src->score;
}

unsigned long int grid_score(grid g){
  return g->score;
}

tile get_tile(grid g,int x,int y){
  return g->tiles[y][x];
}

void set_tile (grid g, int x, int y, tile t){
  g->tiles[y][x]=t;
}

bool can_move(grid g,dir d){
  bool cm = false;
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=1;x<GRID_SIDE;x++){
      switch(d)
	{
	case UP:
	  if((g->tiles[x-1][y]==0) ^ (g->tiles[x][y]==g->tiles[x-1][y]))
	    cm=true;
	  break;
	case LEFT:
	  if((g->tiles[y][x-1]==0) ^ (g->tiles[y][x]==g->tiles[y][x-1]))
	    cm=true;
	  break;
	case DOWN:
	  if((g->tiles[x][y]==0) ^ (g->tiles[x-1][y]==g->tiles[x][y]))
	    cm=true;
	  break;
	case RIGHT:
	  if((g->tiles[y][x]==0) ^ (g->tiles[y][x-1]==g->tiles[y][x]))
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

void do_move(grid g, dir d){ 
  int size = 0;
  int array[GRID_SIDE];
  if(can_move(g,d)) {
    for(int x=0;x<GRID_SIDE;x++)
      {
	//Faire Doc grid_utilities.h
	//Expliquer la méthode utilisée
	//d>=2 <=> d==DOWN || d==RIGHT
	//d%2 <=> d==LEFT || d==RIGHT
	grid_to_array(g,array,&size,x,(d>=2),(d%2));
	g->score+=compute_array(array,&size);
	array_to_grid(g,array,&size,x,(d>=2),(d%2));
      }
  }
}

void add_tile(grid g){
  //DEBUT ARRAYLEAU DES VIDES
  int **array = malloc(GRID_SIDE*GRID_SIDE*sizeof(int*));
  int size=0;
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      if(get_tile(g,x,y)==0){
        array[size] = malloc(2*sizeof(int));
	array[size][0]=x;
	array[size][1]=y;
	size++;
      }
    }
  }
  //FIN ARRAYLEAU DES VIDES
  if(size>=1){
    //DEBUT RANDOM rand()%size
    int alea = rand()%1000;
    int pos_alea = rand()%size;
    if (alea<900)
      set_tile(g,array[pos_alea][0],array[pos_alea][1],1);
    else
      set_tile(g,array[pos_alea][0],array[pos_alea][1],2);
    //FIN RANDOM
  }

  //DEBUT FREE
  for(int i=0;i<size;i++)
    free(array[i]);
  free(array);
  //FIN FREE
}

void play(grid g, dir d){
  if(can_move(g,d)) {
    do_move(g,d);
    add_tile(g);
  }
}

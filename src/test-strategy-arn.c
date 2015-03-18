#include <grid.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int nb_vide(grid g){
  int c=0;
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      if(get_tile(g,x,y)==0)
	c++;
    }
  }
  return c;
}

int score(grid g){

  return grid_score(g);

}

int gps(grid g){
  int score_max = 0;
  int dir = 0;
  //grid g_tab[GRID_SIDE*GRID_SIDE];
  grid g_copie = new_grid();
  
  for(int i=0;i<4;i++){
    if(can_move(g,i)){
      copy_grid(g,g_copie); //On reprend une copie
      int score_total = 0; //Initialise le score total des possibilitées
      do_move(g_copie,i); //On move

      int x=0;
      int y=0;
    
      for(int p=0;p<nb_vide(g_copie);p++){
	if(get_tile(g_copie,x,y)==0){
	  set_tile(g_copie,x,y,1);
	  score_total+=score(g_copie);
	  set_tile(g_copie,x,y,0);
	  if(x<GRID_SIDE-1)
	    x++;
	  else{
	    x=0;
	    y++;
	  }
	}
      }

      if(score_total>=score_max){
	score_max = score_total;
	dir = i;
      }
    }
  }
  //printf("score max : %d\n",score_max);
  return dir;
}


int main(void){
  srand(time(NULL));
  grid g = new_grid();
  add_tile(g);
  add_tile(g);

  draw_grid(g);
  
  printf("NB VIDE : %d\n",nb_vide(g));

  printf("DIR : %d\n",gps(g));
  int i=0;
  while(!game_over(g) && i<30){
    play(g,gps(g));
    i++;
  }

  draw_grid(g);
  
  return EXIT_SUCCESS;
}

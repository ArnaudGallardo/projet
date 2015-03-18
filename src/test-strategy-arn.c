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

int nb_max(grid g){
  int max=0;
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      if(get_tile(g,x,y)>max)
	max=get_tile(g,x,y);
    }
  }
  return max;
}

int score(grid g){
  int score=0;
  //Partie 1 : Au coin !
  int score_coin[4];

  score_coin[0]=0;//Coin Bas Droite
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      score_coin[0]+=get_tile(g,x,y)*(x*y);
    }
  }
  score_coin[1]=0;//Coin Bas Gauche
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      score_coin[1]+=get_tile(g,GRID_SIDE-1-x,y)*(x*y);
    }
  }
  score_coin[2]=0;//Coin Haut Gauche
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      score_coin[2]+=get_tile(g,GRID_SIDE-1-x,GRID_SIDE-1-y)*(x*y);
    }
  }
  score_coin[3]=0;//Coin Haut Droite
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      score_coin[3]+=get_tile(g,x,GRID_SIDE-1-y)*(x*y);
    }
  }
  int max=0;
  int imax=0;
  for(int i=0;i<4;i++){
    if(score_coin[i]>max){
      max=score_coin[i];
      imax=i;
    }
  }
  score+=score_coin[imax]*score_coin[imax]-score_coin[0]-score_coin[1]-score_coin[2]-score_coin[3];
  //score+=score_coin[imax];
  //printf("%d\n",2*score_coin[imax]-score_coin[0]-score_coin[1]-score_coin[2]-score_coin[3]);
  //score+=grid_score(g);
  
  return score;

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


void gps2(grid g, int etage,int * tab){
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

	  if(etage<15){//FIXER ETAGE MAX ICI
	    gps2(g_copie,++etage,tab);
	    score_total+=tab[0]*(etage);
	  }
	  
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
  tab[0]=score_max;
  tab[1]=dir;
}


int main(void){
  srand(time(NULL));
  grid g = new_grid();
  add_tile(g);
  add_tile(g);

  draw_grid(g);
  
  printf("NB VIDE : %d\n",nb_vide(g));
  int tab[2];
  tab[0]=0;
  tab[1]=0;
  //gps2(g,0,tab);
  printf("DIR : %d\n",tab[1]);
  int i=0;
  while(!game_over(g)){
    gps2(g,0,tab);
    play(g,tab[1]);
    //draw_grid(g);
    i++;
  }

  draw_grid(g);
  printf("Score final : %ld\nNombre de coup: %d\n",grid_score(g),i);
  
  return EXIT_SUCCESS;
}

#include <grid.h>

int fast(grid g){
  if(can_move(g,0)){
    return 0;
  }
  if(can_move(g,1)){
    return 1;
  }
  if(can_move(g,2)){
    return 2;
  }
  if(can_move(g,3)){
    return 3;
  }
}

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
  int puissance_case = 0;
  score_coin[0]=0;//Coin Bas Droite
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      puissance_case = (x+1)*(y+1);
      score_coin[0]+=get_tile(g,x,y)*puissance_case;
    }
  }
  score_coin[1]=0;//Coin Bas Gauche
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      puissance_case = (x+1)*(y+1);
      score_coin[1]+=get_tile(g,GRID_SIDE-1-x,y)*puissance_case;
    }
  }
  score_coin[2]=0;//Coin Haut Gauche
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      puissance_case = (x+1)*(y+1);
      score_coin[2]+=get_tile(g,GRID_SIDE-1-x,GRID_SIDE-1-y)*puissance_case;
    }
  }
  score_coin[3]=0;//Coin Haut Droite
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      puissance_case = (x+1)*(y+1);
      score_coin[3]+=get_tile(g,x,GRID_SIDE-1-y)*puissance_case;
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
  score+=score_coin[imax];
  
  //Partie 2 : Nombre de cases vides !
  score*=(nb_vide(g)/(GRID_SIDE*GRID_SIDE));

  //Partie 3 : Cases identiques !

  
  
  return score;

}

int efficient(grid g){
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


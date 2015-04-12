#include <grid.h>
#include <stdio.h>

long int score_rand_arnaud(grid g,int etage,int etage_max, double proba);
long int score_dir_arnaud(grid g, int etage, int etage_max, double proba);
int NB_DIR=4;

int fast(grid g){
  printf("fast");
  if(can_move(g,0)){
    return 0;
  }
  if(can_move(g,1)){
    return 1;
  }
  if(can_move(g,2)){
    return 2;
  }
  return 3;
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

long int score(grid g){
  long int score=0;
  //Partie 1 : Au coin !
  /*long int score_coin[4];
  long int puissance_case = 0;
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
  long int max=0;
  int imax=0;
  for(int i=0;i<NB_DIR;i++){
    if(score_coin[i]>max){
      max=score_coin[i];
      imax=i;
    }
  }
  score+=score_coin[imax];
  */
  int c=0;
  for(int y=0;y<GRID_SIDE;y++){
    for(int x=1;x<GRID_SIDE;x++){
      if(y%2==0) {
	 if(get_tile(g,x,y)>get_tile(g,x-1,y))
	   c++;
      }
      else {
	if(get_tile(g,GRID_SIDE-x+1,y)>get_tile(g,GRID_SIDE-x,y))
	   c++;
      }
    }
  }
  
  score+= (c*100)/16;
  //Partie 2 : Nombre de cases vides !
  score+=(nb_vide(g)*100)/16;
  //Partie 2bis : Case max !
  score+=(nb_max(g)*100)/2048;
  //Partie 3 : Cases identiques !
  long int r=0;
  for(int i=0; i<GRID_SIDE; i++){
    for(int j=0; j<GRID_SIDE; j++){
      for(int x=-1; x<2; x++){
	for(int y=-1; y<2; y++){
	  if((x+y%2)!= 0){ // truc yolo de timo sur les diagonales non diagonales
	    if(i+x>= 0 && j+y>= 0 && i+x< GRID_SIDE && j+y< GRID_SIDE){
	      if(get_tile(g, i+x, j+y)== get_tile(g, i, j)){
		r++;
	      }
	    }
	    else
	      r++;
	  }
	}
      }
    }
  }

  score+=(r*100)/54;
  
  
  return score;

}

int efficient(grid g){
  int score_max = 0;
  int dir = 0;
  //grid g_tab[GRID_SIDE*GRID_SIDE];
  grid g_copie = new_grid();
  
  for(int i=0;i<NB_DIR;i++){
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

long int score_dir_arnaud(grid g, int etage, int etage_max,double proba) {
  long int score_total=0;
  //printf("d=%d ",etage);
  for(int i=0;i<4;i++) {
    if(can_move(g,i)) {
      grid g1 = new_grid();
      copy_grid(g,g1);
      do_move(g1,i);
      score_total+=score_rand_arnaud(g1,etage+1,etage_max,proba*(1/4));
      delete_grid(g1);
    }
  }
  return score_total;
}

long int score_rand_arnaud(grid g,int etage,int etage_max, double proba) {
  int x = 0;
  int y = 0;
  long int score_total=0;
  //printf("r=%d ",etage);
  int score_max=0;
  for(int p=0;p<nb_vide(g);p++){
    if(get_tile(g,x,y)==0) {
      if(etage>=etage_max) {
	set_tile(g,x,y,1);
	//score_total+=score(g);
	if(score(g)>score_max)
	  score_max=score(g)*proba*(1/nb_vide(g))*(9/10);
	set_tile(g,x,y,0);
	set_tile(g,x,y,2);
	//score_total+=score(g);
	if(score(g)>score_max)
	  score_max=score(g)*proba*(1/nb_vide(g))*(1/10);
	set_tile(g,x,y,0);
      }
      else {
	set_tile(g,x,y,1);
	score_total+=score_dir_arnaud(g,etage+1,etage_max,proba*(1/nb_vide(g))*(9/10));
	set_tile(g,x,y,0);
	set_tile(g,x,y,2);
	score_total+=score_dir_arnaud(g,etage+1,etage_max,proba*(1/nb_vide(g))*(1/10));
	set_tile(g,x,y,0);
      }
    }
    if(x<GRID_SIDE-1)
      x++;
    else{
      x=0;
      y++;
    }
  }
  return score_total/(nb_vide(g)+1);
}

int gps_arnaud(grid g) {
  //printf("gps_arnaud\n");
  long int scores[4];
  int etage_max = 4;
  if(nb_vide(g)>1)
    etage_max=16/nb_vide(g);
  else
  etage_max=10;
  for(int i=0;i<4;i++) {
    grid g1 = new_grid();
    copy_grid(g,g1);
    do_move(g1,i);
    scores[i]=score_rand_arnaud(g1,0,etage_max,1);
    delete_grid(g1);
  }
  long int tmp_max=0;
  int i_max=0;
  for(int j=0;j<4;j++) {
    if(can_move(g,j)) {
      if(scores[j]>=tmp_max) {
	tmp_max=scores[j];
	i_max=j;
      }
    }
  }
  //printf("\n");
  return i_max;
}

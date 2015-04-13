#include <grid.h>
#include <stdio.h>

long int score_rand_arnaud(grid g,int etage,int etage_max, int * dirs);
long int score_dir_arnaud(grid g, int etage, int etage_max, int * dirs);
int NB_DIR=4;

float power(float f,int n) {
  if( n>1 )
    return (f*power(f,n-1));
  return 1;
}

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


long int score(grid g, int* dirs){
  long int score=0;
  int tmp[4];
  for(int i=0;i<NB_DIR;i++) {
    tmp[dirs[i]]++;
  }
  int tmp_m=0;
  int i_m1=-1;
  for(int j=0;j<4;j++) {
    if(tmp[j]>tmp_m) {
      i_m1=j;
      tmp_m=tmp[j];
    }
  }
  tmp[i_m1]=0;
  tmp_m=0;
  int i_m2=-1;
  for(int j=0;j<4;j++) {
    if(tmp[j]>tmp_m) {
      i_m2=j;
      tmp_m=tmp[j];
    }
  }

  int i_m=0;

  if(i_m1==0) {
    if(i_m2==1)
      i_m=0;
    if(i_m2==2)
      i_m=-1;
    if(i_m2==3)
      i_m=1;
  }
  if(i_m1==1) {
    if(i_m2==0)
      i_m=0;
    if(i_m2==2)
      i_m=3;
    if(i_m2==3)
      i_m=-1;
  }
  if(i_m1==2) {
    if(i_m2==0)
      i_m=-1;
    if(i_m2==1)
      i_m=3;
    if(i_m2==3)
      i_m=2;
  }
  if(i_m1==3) {
    if(i_m2==0)
      i_m=1;
    if(i_m2==1)
      i_m=-1;
    if(i_m2==2)
      i_m=2;
  }

  //Partie 1 : Au coin !
  float ratio_init = 0.2;
  float c[8];
  //--|
  c[0]=0.0;
  float ratio = ratio_init;
  for(int y=0;y<GRID_SIDE;y++){
    for(int x=0;x<GRID_SIDE;x++){
      if(y%2==0) {
	c[0]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[0]+=get_tile(g,GRID_SIDE-x-1,y)*ratio;
      }
      //printf("ratio : %f\n",ratio);
      ratio*=ratio;
    }
  }
  //_|
  ratio = ratio_init;
  c[1]=0.0;
  for(int x=GRID_SIDE-1;x>=0;x--){
    for(int y=0;y<GRID_SIDE;y++){
      if(x%2!=0) {
	c[1]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[1]+=get_tile(g,x,GRID_SIDE-y-1)*ratio;
      }
      ratio*=ratio;
    }
  }
  //|__
  ratio = ratio_init;
  c[2]=0.0;
  for(int y=GRID_SIDE-1;y>=0;y--){
    for(int x=GRID_SIDE-1;x>=0;x--){
      if(y%2!=0) {
	c[2]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[2]+=get_tile(g,GRID_SIDE-x-1,y)*ratio;
      }
      ratio*=ratio;
    }
  }
//|-
  ratio = ratio_init;
  c[3]=0.0;
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=GRID_SIDE-1;y>=0;y--){
      if(x%2==0) {
	c[3]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[3]+=get_tile(g,x,GRID_SIDE-y-1)*ratio;
      }
      ratio*=ratio;
    }
  }
  //|-
  ratio = ratio_init;
  c[4]=0.0;
  for(int y=0;y<GRID_SIDE;y++){
    for(int x=GRID_SIDE-1;x>=0;x--){
      if(y%2==0) {
	c[4]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[4]+=get_tile(g,GRID_SIDE-x-1,y)*ratio;
      }
      ratio*=ratio;
    }
  }
  //-|
  ratio = ratio_init;
  c[5]=0.0;
  for(int x=GRID_SIDE-1;x>=0;x--){
    for(int y=GRID_SIDE-1;y>=0;y--){
      if(x%2!=0) {
	c[5]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[5]+=get_tile(g,x,GRID_SIDE-y-1)*ratio;
      }
      ratio*=ratio;
    }
  }
  //_|
  ratio = ratio_init;
  c[6]=0.0;
  for(int y=GRID_SIDE-1;y>=0;y--){
    for(int x=0;x<GRID_SIDE;x++){
      if(y%2!=0) {
	c[6]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[6]+=get_tile(g,GRID_SIDE-x-1,y)*ratio;
      }
      ratio*=ratio;
    }
  }
  //|_
  ratio = ratio_init;
  c[7]=0.0;
  for(int x=0;x<GRID_SIDE;x++){
    for(int y=0;y<GRID_SIDE;y++){
      if(x%2==0) {
	c[7]+=get_tile(g,x,y)*ratio;
      }
      else {
	c[7]+=get_tile(g,x,GRID_SIDE-y-1)*ratio;
      }
      ratio*=ratio;
    }
  }
  
  float cb[4];
  cb[0]=c[0]+c[7];
  cb[1]=c[1]+c[4];
  cb[2]=c[2]+c[5];
  cb[3]=c[3]+c[6];
  if(i_m!=-1)
    cb[i_m]*=2;

  float max=-1;
  int i_max=-1;
  for(int k=0;k<4;k++) {
    if(cb[k]>=max) {
      i_max=k;
      max=cb[k];
    }
  }
  
  score+=(cb[i_max]*10);
  
  //Partie 2 : Nombre de cases vides !
  score+=(nb_vide(g)*100)/16;
  //Partie 2bis : Case max !
  //score+=(nb_max(g)*100)/2048;
  
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

  score+=(r*100)/96;
  //printf("truc tim %d \n",(r*100)/96);
  
  //Partie 2ter : Pas de GO
  if(game_over(g))
    score-=50;
  
  score+=grid_score(g)/100;

int tile_max = nb_max(g);
  if(get_tile(g,0,0)!=tile_max && get_tile(g,GRID_SIDE-1,0)!=tile_max && get_tile(g,0,GRID_SIDE-1)!=tile_max && get_tile(g,GRID_SIDE-1,GRID_SIDE-1)!=tile_max)
    score/=2;

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
	  //score_total+=score(g_copie,);
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

long int score_dir_arnaud(grid g, int etage, int etage_max, int * dirs) {
  long int score_total=0;
  //printf("d=%d ",etage);
  for(int i=0;i<4;i++) {
    if(can_move(g,i)) {
      grid g1 = new_grid();
      copy_grid(g,g1);
      do_move(g1,i);
      score_total+=score_rand_arnaud(g1,etage+1,etage_max,dirs)+score(g,dirs)*power(0.9,etage_max-etage+1);
      delete_grid(g1);
    }
  }
  return score_total;
}

long int score_rand_arnaud(grid g,int etage,int etage_max, int * dirs) {
  int vides = nb_vide(g);
  /*if(vides>13)
    etage_max=2;
  else if (vides<=13 && vides>10)
    etage_max=2;
  else if (vides<=10 && vides>8)
    etage_max=3;
  else if(vides<=8 && vides>5)
    etage_max=4;
  else if(vides<=5 && vides>3)
    etage_max=6;
  else
    etage_max=8;*/
  if(vides<5)
    etage_max=6;
  if(vides<2)
    etage_max=8;
  int x = 0;
  int y = 0;
  long int score_total=0;
  //printf("r=%d ",etage);
  //int score_max=0;
  for(int p=0;p<vides;p++){
    if(get_tile(g,x,y)==0) {
      if(etage>=etage_max) {
	set_tile(g,x,y,1);
	score_total+=score(g,dirs);
	/*if(score(g)>score_max) {
	  prob_final = proba*(100/(nb_vide(g)+1))*(90/100)*100;
	  score_max=score(g)*prob_final;
	  }*/
	set_tile(g,x,y,0);
	set_tile(g,x,y,2);
	score_total+=score(g,dirs);
	/*if(score(g)>score_max) {
	  prob_final = proba*(100/(nb_vide(g)+1))*(10/100)*100;
	  score_max=score(g)*prob_final;
	  }*/
	set_tile(g,x,y,0);
      }
      else {
	set_tile(g,x,y,1);
	score_total+=score_dir_arnaud(g,etage+1,etage_max,dirs)+score(g,dirs)*power(0.9,etage_max-etage+1);
	set_tile(g,x,y,0);
	set_tile(g,x,y,2);
	score_total+=score_dir_arnaud(g,etage+1,etage_max,dirs)+score(g,dirs)*power(0.9,etage_max-etage+1);
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
  return score_total/(vides+1);
}

int gps_arnaud(grid g, int * dirs) {
  //printf("gps_arnaud\n");
  long int scores[4];
  int etage_max = 4;
  for(int i=0;i<4;i++) {
    grid g1 = new_grid();
    copy_grid(g,g1);
    do_move(g1,i);
    scores[i]=score_rand_arnaud(g1,0,etage_max,dirs);
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
  int b = 0;
  int k = 0;
  while (k<NB_DIR) {
    if (dirs[k]==-1) {
      dirs[k]=i_max;
      b=1;
      break;
    }
    else
      k++;
  }
  if(b!=1) {
    for(int l=0;l<NB_DIR-1;l++) {
      dirs[l]=dirs[l+1];
    }
    dirs[NB_DIR-1]=i_max;
  }
  return i_max;
}

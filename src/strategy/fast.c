#include <stdlib.h>
#include "strategy.h"

long int score(grid g){
  long int score=0;

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

  float max=-1;
  int i_max=-1;
  for(int k=0;k<4;k++) {
    if(cb[k]>=max) {
      i_max=k;
      max=cb[k];
    }
  }
  
  score+=(cb[i_max]*10);


  return score;

}


int fast(grid g){
  if(can_move(g,0)){
    return 0;
  }
  if(can_move(g,1)){
    return 1;
  }
  int sc2=0;
  if(can_move(g,2)) {
    grid g2 = new_grid();
    copy_grid(g,g2);
    do_move(g2,2);
    add_tile(g2);
    sc2=score(g2);
    delete_grid(g2);
  }
  int sc3=0;
  if(can_move(g,3)) {
    grid g3 = new_grid();
    copy_grid(g,g3);
    do_move(g3,3);
    add_tile(g3);
    sc2=score(g3);
    delete_grid(g3);
  }
  if(sc2>sc3)
    return 2;
  return 3;
}

strategy A2_bifert_daubasse_gallardo_fast()
{
  strategy s = malloc(sizeof(struct strategy_s));
  int dirs[4];
  for(int i=0;i<4;i++)
    dirs[i]=-1;
  s->play_move = fast;
  s->mem = (void *) true;
  s->free_strategy = free_memless_strat;
  return s;
}

void free_memless_strat(strategy s)
{
  free(s);
}

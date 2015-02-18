#include "grid.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)

void resultat(bool result)
{
  if(result){
    couleur("32");
    printf("OK");
  }
  else {
    couleur("31");
    printf("KO");
  }
  couleur("0");
}

bool equals(grid g1, grid g2)
{
  bool result = true;
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(g1,i,j)!=get_tile(g2,i,j))
	    result = false;
	}
    }
  if(grid_score(g1)!=grid_score(g2))
    result=false;
  return result;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  couleur("36");
  printf("Debut du test 1 :\n");
  couleur("0");
  bool ok = true;
  
  printf("\nTest new_grid :\t\t");
  grid g = new_grid();
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(g,i,j)!=0)
	    ok = false;
	}
    }
  resultat(ok);

  printf("\nTest copy_grid :\t");
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,5);
  set_tile(g,GRID_SIDE/2,(GRID_SIDE/2)-1,5);
  do_move(g,UP);
  grid f = new_grid();
  copy_grid(g,f);
  resultat(equals(g,f));
  delete_grid(g);
  delete_grid(f);

  printf("\nTest can_move :\t\t");
  f = new_grid();
  set_tile(f,0,0,2);
  g = new_grid();
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,5);
  ok = can_move(g,UP) && can_move(g,DOWN) && can_move(g,RIGHT) && can_move(g,LEFT)  && !(can_move(f,UP)) && !(can_move(f,LEFT)) && can_move(f,RIGHT) && can_move(f,DOWN);
  resultat(ok);

  printf("\nTest do_move :\t\t");
  do_move(g,UP);
  ok = !(can_move(g,UP)) && can_move(g,DOWN) && can_move(g,RIGHT) && can_move(g,LEFT);
  do_move(g,LEFT);
  ok = ok && (!(can_move(g,UP)) && can_move(g,DOWN) && can_move(g,RIGHT) && !(can_move(g,LEFT)));
  resultat(ok);
  
  printf("\nTest add_tile :\t\t");
  ok = true;
  grid h = new_grid();
  for(int i=0;i<GRID_SIDE*GRID_SIDE;i++)
    add_tile(h);
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(h,i,j)==0)
	    ok = false;
	}
    }
  resultat(ok);
  delete_grid(h);
  
  printf("\nTest proba 2 ou 4 :\t");
  int deux = 0;
  int quatre = 0;
  h = new_grid();
  for(int i=0;i<100000;i++)
    {
    add_tile(h);
    for(int i=0;i<GRID_SIDE;i++)
      {
	for(int j=0;j<GRID_SIDE;j++)
	  {
	    if(get_tile(h,i,j)==1)
	      deux+=1;
	    else if(get_tile(h,i,j)==2)
	      quatre+=1;
	    set_tile(h,i,j,0);
	  }
      }
    }
  deux/=1000;
  quatre/=1000;
  if(deux<=91 && deux>=89)
    ok = true;
  else
    ok = false;
  resultat(ok);
  printf("\t(%d%% : %d%%)",deux,100-deux);

  printf("\nTest proba position :\t");
  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  h = new_grid();
  for(int i=0;i<GRID_SIDE;i++){
    for(int j=0;j<GRID_SIDE;j++)
      set_tile(h,i,j,2);
  }
  for(int k=0;k<100000;k++)
    {
      set_tile(h,2,3,0);
      set_tile(h,3,1,0);
      set_tile(h,3,3,0);
      add_tile(h);
      if(get_tile(h,2,3)!=0)
	c1+=1;
      else if(get_tile(h,3,1)!=0)
	c2+=1;
      else if(get_tile(h,3,3)!=0)
	c3+=1;
    }
  int i = 1;
  c1/=1000;
  c2/=1000;
  c3/=1000;
  ok = c1<=33+i && c1>=33-i;
  ok = ok && c2<=33+i && c2>=33-i;
  ok = ok && c3<=33+i && c3>=33-i;
  resultat(ok);
  printf("\t(%d%% : %d%% : %d%%)\n",c1,c2,c3);
  
  delete_grid(g);
  delete_grid(f);
  delete_grid(h);
}

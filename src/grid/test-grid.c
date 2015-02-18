#include "grid.h"
#include <stdio.h>
#include <stdbool.h>

#define couleur(param) printf("\033[%sm",param)

void resultat(bool result)
{
  if(result){
    couleur("32");
    printf("OK\n");
  }
  else {
    couleur("31");
    printf("KO\n");
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
  return result;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  couleur("36");
  printf("Debut du test 1 :\n");
  couleur("0");
  bool ok = true;
  
  printf("Test new_grid :\t\t");
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

  printf("Test copy_grid :\t");
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,5);
  grid f = new_grid();
  copy_grid(g,f);
  resultat(equals(g,f));

  printf("Test can_move :\t\t");
  set_tile(f,GRID_SIDE/2,GRID_SIDE/2,0);
  set_tile(f,0,0,2);
  ok = can_move(g,UP) && can_move(g,DOWN) && can_move(g,RIGHT) && can_move(g,LEFT)  && !(can_move(f,UP)) && !(can_move(f,LEFT)) && can_move(f,RIGHT) && can_move(f,DOWN);
  resultat(ok);

  printf("Test add_tile :\t\t");
  ok = true;
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,0);
  for(int i=0;i<GRID_SIDE*GRID_SIDE;i++)
    add_tile(g);
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(g,i,j)==0)
	    ok = false;
	}
    }
  resultat(ok);
  
  delete_grid(g);
}

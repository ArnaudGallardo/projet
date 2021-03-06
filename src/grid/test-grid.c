#include "grid.h"
#include "grid_utilities.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define color(param) printf("\033[%sm",param)

/**
 * \brief Print the result of the test : green OK when passed, red KO when failed.
 */
void result(bool result)
{
  if(result){
    color("32");
    printf("OK");
  }
  else {
    color("31");
    printf("KO");
  }
  color("0");
}

void title(char* title)
{
  color("35");
  printf("\n%s",title);
  color("0");
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  color("36");
  printf("Beginning of test 1 (%s) :\n",argv[0]);
  color("0");
  bool ok = true;
  
  title("General functions :");

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
  result(ok);

  printf("\nTest copy_grid :\t");
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,5);
  set_tile(g,GRID_SIDE/2,(GRID_SIDE/2)-1,5);
  do_move(g,UP);
  grid f = new_grid();
  copy_grid(g,f);
  result(equals(g,f));

  printf("\nTest grid_score :\t");
  result(grid_score(g)==64);
  
  delete_grid(g);
  delete_grid(f);

  printf("\nTest can_move :\t\t");
  f = new_grid();
  set_tile(f,0,0,2);
  g = new_grid();
  set_tile(g,GRID_SIDE/2,GRID_SIDE/2,5);
  ok = can_move(g,UP) && can_move(g,DOWN) && can_move(g,RIGHT) && can_move(g,LEFT)  && !(can_move(f,UP)) && !(can_move(f,LEFT)) && can_move(f,RIGHT) && can_move(f,DOWN);
  result(ok);

  printf("\nTest do_move :\t\t");
  do_move(g,UP);
  ok = !(can_move(g,UP)) && can_move(g,DOWN) && can_move(g,RIGHT) && can_move(g,LEFT);
  do_move(g,LEFT);
  ok = ok && (!(can_move(g,UP)) && can_move(g,DOWN) && can_move(g,RIGHT) && !(can_move(g,LEFT)));
  result(ok);
  
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
  result(ok);
  delete_grid(h);
  
  title("Probability functions :");

  printf("\nTest proba 2 ou 4 :\t");
  int two = 0;
  int four = 0;
  h = new_grid();
  for(int i=0;i<100000;i++)
    {
    add_tile(h);
    for(int i=0;i<GRID_SIDE;i++)
      {
	for(int j=0;j<GRID_SIDE;j++)
	  {
	    if(get_tile(h,i,j)==1)
	      two+=1;
	    else if(get_tile(h,i,j)==2)
	      four+=1;
	    set_tile(h,i,j,0);
	  }
      }
    }
  two/=1000;
  four/=1000;
  if(two<=91 && two>=89)
    ok = true;
  else
    ok = false;
  result(ok);
  if(!ok)
    printf("\t(%d%% : %d%%)",two,100-two);

  delete_grid(h);
  
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
  result(ok);
  if(!ok)
    printf("\t(%d%% : %d%% : %d%%)",c1,c2,c3);
 
  title("Personal functions :");

  printf("\nTest invert_array :\t");
  int tableau[GRID_SIDE];
  for(int i=0;i<GRID_SIDE;i++){
    tableau[i]=i;
  }
  i=GRID_SIDE;
  ok=true;
  invert_array(tableau,&i);
  for(int j=0;j<GRID_SIDE;j++)
    {
      if(tableau[j]!=GRID_SIDE-j-1)
	ok=false;
    }
  result(ok);

  printf("\nTest grid->array :\t");
  set_tile(h,0,3,3);
  set_tile(h,2,3,0);
  set_tile(h,3,3,1);
  ok=true;
  grid_to_array(h,tableau,&i,3,false,true);
  i=0;
  for(int j=0;j<GRID_SIDE;j++)
    {
      if(get_tile(h,j,3)!=0)
	{
	  if(get_tile(h,j,3)!=tableau[i])
	    ok=false;
	  i++;
	}
    }
  result(ok);

  printf("\nTest compute_array :\t\t");
  compute_array(tableau,&i);
  ok = true;
  for(int j=0;j<i;j++)
    {
      if(tableau[j]!=i-j)
	ok=false;
    }
  result(ok);

  printf("\nTest array->grid :\t");
  ok = true;
  array_to_grid(h,tableau,&i,3,false,true);
  i=0;
  for(int j=0;j<GRID_SIDE;j++)
    {
      if(get_tile(h,j,3)!=0)
	{
	  if(get_tile(h,j,3)!=tableau[i])
	    ok=false;
	  i++;
	}
    }
  result(ok);

  delete_grid(g);
  delete_grid(f);
  delete_grid(h);
  printf("\n");
}

#include "grid.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  
  srand(time(NULL));

  grid g = new_grid();
  set_tile(g,2,2,3);
  draw_grid(g);
  if(can_move(g,UP))
    printf("CAN MOVE\n");
  else
    printf("CANT MOVE\n");
  printf("Do move UP :\n");
  do_move(g,UP);
  draw_grid(g);
  if(can_move(g,UP))
    printf("CAN MOVE\n");
  else
    printf("CANT MOVE\n");
  printf("Add tile :\n");
  add_tile(g);
  draw_grid(g);
  delete_grid(g);

}

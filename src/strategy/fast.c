#include <grid.h>


int fast(g){
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

#include "grid.h"
#include "grid_utilities.h"


/**
 * \brief Print the grid in the default output.
 */
void draw_grid(grid g){
  printf("-------------\n");
  for(int y=0;y<GRID_SIDE;y++) {
    for(int x=0;x<GRID_SIDE;x++){
      printf("%i",g->tiles[y][x]);
    }
    printf("\n");
  }
  printf("-------------\n");
}


/**
 * \brief Check the equality of two grids.
 * \return true if equals, false if not equals
 */
bool equals(grid g1, grid g2)
{
  bool res = true;
  for(int i=0;i<GRID_SIDE;i++)
    {
      for(int j=0;j<GRID_SIDE;j++)
	{
	  if(get_tile(g1,i,j)!=get_tile(g2,i,j))
	    res = false;
	}
    }
  if(grid_score(g1)!=grid_score(g2))
    res=false;
  return res;
}


/**
 * \brief Compute the new line array
 */
int compute_array(int array[], int *size){ //CHANGER NOM FCTION
  int score=0;
  for(int i=1;i<*size;i++){
    if(array[i-1]==array[i]) {
      array[i-1]+=1;
      score+=pow(2,array[i-1]);
      for(int j=i+1;j<*size;j++){
	array[j-1]=array[j];
      }
      *size-=1;
    }
  }
  return score;
}

/**
 * \brief Transform a grid line into an usable line array
 * \param g the grid to use
 * \param array the line array
 * \param size the size of the line array
 * \param x one of the position parameter
 */
void grid_to_array(grid g, int array[], int *size, int x, bool invert, bool horizontal)
{
  *size=0;
  int tmp = x;
  for(int y=0;y<GRID_SIDE;y++){
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(get_tile(g,x,y)!=0){
      array[*size]=get_tile(g,x,y);
      *size+=1;
    }
    if(horizontal)
      y=x;
  }
  if(invert)
    invert_array(array, size);
}

/**
 * \brief Reverse an array
 * \param array the array to reverse
 * \param size the size of the array
 */
void invert_array(int array[], int *size)
{
  int tmp;
  for(int i=0;i<*size/2;i++)
    {
      tmp = array[i];
      array[i]=array[*size-i-1];
      array[*size-i-1]=tmp;
    }
}

/**
 * \brief Copy an line array into a grid line
 * \param g the grid
 * \param array the line array
 * \param size the size of the line array
 * \param x the position of the line in the grid
 */
void array_to_grid(grid g, int array[], int *size, int x, bool invert, bool horizontal)
{
  int tmp = x;
  int tp;
  for(int y=0;y<GRID_SIDE;y++){
    tp = y;
    if(horizontal)
      {
	x = y;
	y = tmp;
      }
    if(invert)
      {
	if(tp<GRID_SIDE-(*size))
	  set_tile(g,x,y,0);
	else
	  set_tile(g,x,y,array[GRID_SIDE-tp-1]);
      }
    else
      {
	if(tp<*size)
	  set_tile(g,x,y,array[tp]);
	else
	  set_tile(g,x,y,0);
      }
    if(horizontal)
      y=x;
  }
}

#include <stdlib.h>
#include <time.h>
#include <grid.h>
#include <ncurses.h>


int main(int argc, char *argv[])
{	
	srand(time(NULL));
	grid g = new_grid();
	add_tile(g);
	add_tile(g);
	/*for(int i=0;i<GRID_SIDE;i++) {
	  for(int j=0;j<GRID_SIDE;j++) {
	    set_tile(g,i,j,11);
	  }
	}*/
	draw_grid(g);
	int i;
	i = gps_arnaud(g);
	do_move(g,i);
	draw_grid(g);
	//i=score(g);
	printf("%ld\n",i);
	//printf("%f\n",pow(2,11));
}

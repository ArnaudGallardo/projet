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
	draw_grid(g);
	long int i;
	//i = gps_arnaud(g);
	//do_move(g,i);
	//draw_grid(g);
	i=score(g);
	printf("%ld",i);
}

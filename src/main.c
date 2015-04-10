#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <grid.h>


WINDOW *create_newwin(int height, int width, int starty, int startx);
void draw_grid_win(grid g, WINDOW *local_win);
void destroy_win(WINDOW *local_win);
void draw_game_over(grid g);
void update_score(grid,int,int);

int main(int argc, char *argv[])
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;
	srand(time(NULL));
	initscr();
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_RED, COLOR_WHITE);
	init_pair(9, COLOR_RED, COLOR_YELLOW);
	init_pair(10, COLOR_RED, COLOR_GREEN);
	init_pair(11, COLOR_RED, COLOR_CYAN);
	init_pair(12, COLOR_RED, COLOR_BLUE);
	init_pair(13, COLOR_RED, COLOR_MAGENTA);

	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	height = 2*GRID_SIDE + 1;
	width = 5*GRID_SIDE + 1;

	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F2 to exit\n");
	printw("Press F5 to start fast strategy\n");
	printw("Press F6 to start efficient strategy");
 start:
	refresh();
	grid g = new_grid();
	add_tile(g);
	add_tile(g);
        update_score(g,starty-1,startx);
	my_win = create_newwin(height, width, starty, startx);
	draw_grid_win(g,my_win);

	while(((ch = getch()) != KEY_F(2)) && !game_over(g))
	{
	  switch(ch)
	    {
	    case KEY_LEFT:
		play(g,LEFT);
		draw_grid_win(g,my_win);
		update_score(g,starty-1,startx);
		break;
	    case KEY_RIGHT:
	      play(g,RIGHT);
	      draw_grid_win(g,my_win);
	      update_score(g,starty-1,startx);
	      break;
	    case KEY_UP:
	      play(g,UP);
	      draw_grid_win(g,my_win);
	      update_score(g,starty-1,startx);
	      break;
	    case KEY_DOWN:
	      play(g,DOWN);
	      draw_grid_win(g,my_win);
	      update_score(g,starty-1,startx);
	      break;
	    }
	  if(ch == KEY_F(5))
	    {
	      while(!game_over(g))
		{
		  play(g,fast(g));
		  draw_grid_win(g,my_win);
		  update_score(g,starty-1,startx);
		}
	      while((ch = getch()) != KEY_F(2))
		{
		  if(ch == KEY_F(3))
		    {
		      delete_grid(g);
		      goto start;
		    }
		}
	    }
	  if(ch == KEY_F(6))
	    {
	      while(!game_over(g)){
		play(g,gps(g,0));
		draw_grid_win(g,my_win);
		update_score(g,starty-1,startx);
		/*
		play(g,efficient(g));
		draw_grid_win(g,my_win);
		update_score(g,starty-1,startx);
		*/
	      }
	      while((ch = getch()) != KEY_F(2))
		{
		  if(ch == KEY_F(3))
		    {
		      delete_grid(g);
		      goto start;
		    }
		}
	    }
	  
	}

	if(game_over(g))
	  draw_game_over(g);
	delete_grid(g);
	destroy_win(my_win);
	endwin();
	return 0;
}

void update_score(grid g,int starty,int startx)
{
  mvprintw(starty,startx,"Score : %ld",grid_score(g));
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	for(int i=5;i<width-1;i+=5) {
	  mvwaddch(local_win,0,i,ACS_TTEE);
	  mvwvline(local_win,1,i,ACS_VLINE,height-2);
	  mvwaddch(local_win,height-1,i,ACS_BTEE);
	}
	for(int i=2;i<height-1;i+=2){
	  mvwaddch(local_win,i,0,ACS_LTEE);
	  mvwhline(local_win,i,1,ACS_HLINE,width-2);
	  mvwaddch(local_win,i,width-1,ACS_RTEE);
	}
	for(int row=2;row<height-1;row+=2){
	  for(int col=5;col<width-1;col+=5)
	    mvwaddch(local_win,row,col,ACS_PLUS);
	}
	wmove(local_win,0,0);
	wrefresh(local_win);
	return local_win;
}

tile convert_tuile(tile t){
  tile result = (unsigned int)pow(2.0,t);
  return result;
}

void draw_grid_win(grid g, WINDOW *local_win)
{
  int yp=1;
  int xp;
  for(int y=0;y<GRID_SIDE;y++) {
    xp=2;
    for(int x=0;x<GRID_SIDE;x++){
      mvwprintw(local_win,yp,xp-1,"    ");
      if(get_tile(g,x,y)!=0)
	{
	    if(get_tile(g,x,y)<13)
            wattron(local_win,COLOR_PAIR(get_tile(g,x,y)));
        else
            wattron(local_win,COLOR_PAIR(13));
	  int n = convert_tuile(get_tile(g,x,y));
	  int c=0;
	  while(n!=0)
	    {
	      n/=10;
	      ++c;
	    }
	  if (c==4)
	    mvwprintw(local_win,yp,xp-1,"%d",convert_tuile(get_tile(g,x,y)));
	  else if (c==3)
	    mvwprintw(local_win,yp,xp,"%d",convert_tuile(get_tile(g,x,y)));
	  else
	    mvwprintw(local_win,yp,xp,"%d",convert_tuile(get_tile(g,x,y)));

	  if(get_tile(g,x,y)<13)
            wattroff(local_win,COLOR_PAIR(get_tile(g,x,y)));
        else
            wattroff(local_win,COLOR_PAIR(13));
	}
      xp+=5;
    }
    yp+=2;
  }
  wrefresh(local_win);
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	wclear(local_win);
	delwin(local_win);
}

void draw_game_over(grid g)
{
  int ch;
  clear();
  attron(COLOR_PAIR(7));
  printw("GAME OVER\n");
  attroff(COLOR_PAIR(7));
  attron(COLOR_PAIR(4));
  printw("Score : %ld points\n",grid_score(g));
  attroff(COLOR_PAIR(4));
  printw("F2 to exit\n");

  while(((ch = getch()) != KEY_F(2))){

  }
}


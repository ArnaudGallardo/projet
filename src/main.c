#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "grid.h"


WINDOW *create_newwin(int height, int width, int starty, int startx);
void draw_grid_win(grid g, WINDOW *local_win);
void destroy_win(WINDOW *local_win);
void draw_game_over(grid g);
void update_score(grid,int,int);
void test(grid g);
void save_score(grid g,char* pseudo);
void draw_score();

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

	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	//height = 9;
	//width = 17;
	height=12;
	width=24;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press F2 to exit");
	refresh();

	grid g = new_grid();
	add_tile(g);
	add_tile(g);
        update_score(g,starty-1,startx);
	my_win = create_newwin(height, width, starty, startx);
	draw_grid_win(g,my_win);

	while(((ch = getch()) != KEY_F(2)) && !game_over(g))
	{	switch(ch)
		{	case KEY_LEFT:
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
	  if(ch==KEY_F(6)){
	    test(g);
	    draw_grid_win(g,my_win);
	  }
	}
	if(game_over(g))
	  draw_game_over(g);
	delete_grid(g);
	destroy_win(my_win);
	endwin();
	return 0;
}

void test(grid g)
{
  add_tile(g);
  set_tile(g,0,0,9);
  set_tile(g,1,0,9);
}

void update_score(grid g,int starty,int startx)
{
  mvprintw(starty,startx,"Score : %ld",grid_score(g));
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0); 
	for(int i=4;i<width-1;i+=4) {
	  mvwvline(local_win,1,i,'|',height-2);
	}
	for(int i=2;i<height-1;i+=2){
	  mvwhline(local_win,i,1,'-',width-2);
	}
	for(int row=2;row<height-1;row+=2){
	  for(int col=4;col<width-1;col+=4)
	    mvwaddch(local_win,row,col,'+');
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
  int xp=2;
  for(int y=0;y<GRID_SIDE;y++) {
    xp=2;
    for(int x=0;x<GRID_SIDE;x++){
      mvwprintw(local_win,yp,xp-1,"   ");
      if(get_tile(g,x,y)!=0)
	{
	  wattron(local_win,COLOR_PAIR(get_tile(g,x,y)));
	  int n = convert_tuile(get_tile(g,x,y));
	  int c=0;
	  while(n!=0)
	    {
	      n/=10;             /* n=n/10 */
	      ++c;
	    }
	  if (c==3)
	    mvwprintw(local_win,yp,xp-1,"%d",convert_tuile(get_tile(g,x,y)));
	  else
	    mvwprintw(local_win,yp,xp,"%d",convert_tuile(get_tile(g,x,y)));
	  wattroff(local_win,COLOR_PAIR(get_tile(g,x,y)));
	}
      xp+=4;
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
  printw("GAME OVER\n");
  printw("F2 to exit\n");
  printw("F3 to restart\n");
  int alea;
  int c;
  FILE *file;
  file = fopen("test.txt", "r");
  if (file) {
    while ((c = getc(file)) != EOF)
      {	  
	alea = rand()%7 +1;
	attron(COLOR_PAIR(alea));
	printw("%c",c);
	attroff(COLOR_PAIR(alea));
      }
    fclose(file);
  }
  while(((ch = getch()) != KEY_F(2))){

  }
  char pseudo[3];
  int i=0;
  printw("Pseudo : ");
  pseudo[0]='A';
  pseudo[1]='A';
  pseudo[2]='A';
  save_score(g,pseudo);
}

void save_score(grid g,char* pseudo)
{
  
  FILE *f = fopen("scoreboard", "a");
  if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  fprintf(f, "%s\t%li\n", pseudo,grid_score(g));

  fclose(f);

}

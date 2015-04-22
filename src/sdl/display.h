#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <grid.h>
#include <grid_utilities.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

extern void eventHappens(grid g); // manage all the callbacks the user presses
extern void draw(); // draw the GUI and run the game with the shortcuts

#endif
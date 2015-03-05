#ifndef _GRID_UTILITIES_H_
#define _GRID_UTILITIES_H_
/**
 * \file grid_utilities.h
 * \brief Contains additional functions needed to play 2048 game.
 **/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "grid.h"

void invert_array(int array[], int *size);

void grid_to_array(grid g, int array[], int *size, int x, bool invert,bool horizontal);

int compute_array(int array[], int *size);

void array_to_grid(grid g, int array[], int *size, int x, bool invert, bool horizontal);

bool equals(grid g1, grid g2);

void draw_grid(grid g);

#endif
